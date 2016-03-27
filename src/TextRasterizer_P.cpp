#include "TextRasterizer_P.h"
#include "TextRasterizer.h"

#include "ignore_warnings_on_external_includes.h"
#include <SkBitmapDevice.h>
#include <SkTypeface.h>
#include <SkUtils.h>
#include "restore_internal_warnings.h"

#include "ICU.h"
#include "CoreResourcesEmbeddedBundle.h"

//#define OSMAND_LOG_CHARACTERS_WITHOUT_FONT 1
#ifndef OSMAND_LOG_CHARACTERS_WITHOUT_FONT
#   define OSMAND_LOG_CHARACTERS_WITHOUT_FONT 0
#endif // !defined(OSMAND_LOG_CHARACTERS_WITHOUT_FONT)

//#define OSMAND_LOG_CHARACTERS_FONT 1
#ifndef OSMAND_LOG_CHARACTERS_FONT
#   define OSMAND_LOG_CHARACTERS_FONT 0
#endif // !defined(OSMAND_LOG_CHARACTERS_FONT)

OsmAnd::TextRasterizer_P::TextRasterizer_P(TextRasterizer* const owner_)
    : owner(owner_)
{
    _defaultPaint.setAntiAlias(true);
    _defaultPaint.setTextEncoding(SkPaint::kUTF16_TextEncoding);
    static_assert(sizeof(QChar) == 2, "If QChar is not 2 bytes, then encoding is not kUTF16_TextEncoding");
}

OsmAnd::TextRasterizer_P::~TextRasterizer_P()
{
}

QVector<OsmAnd::TextRasterizer_P::LinePaint> OsmAnd::TextRasterizer_P::evaluatePaints(
    const QVector<QStringRef>& lineRefs,
    const Style& style) const
{
    // Prepare default paint
    SkPaint paint = _defaultPaint;
    paint.setTextSize(style.size);
    paint.setColor(style.color.toSkColor());

    // Transform text style to font style
    const SkFontStyle fontStyle(
        style.bold ? SkFontStyle::kBold_Weight : SkFontStyle::kNormal_Weight,
        SkFontStyle::kNormal_Width,
        style.italic ? SkFontStyle::kItalic_Slant : SkFontStyle::kUpright_Slant);

    const auto pText = lineRefs.first().string()->constData();

    QVector<LinePaint> linePaints;
    linePaints.reserve(lineRefs.count());
    for (const auto& lineRef : constOf(lineRefs))
    {
        LinePaint linePaint;
        linePaint.line = lineRef;

        TextPaint* pTextPaint = nullptr;
        const auto pLine = lineRef.constData();
        const auto pEnd = pLine + lineRef.size();
        auto pNextCharacter = pLine;
        while (pNextCharacter != pEnd)
        {
            const auto pCharacter = pNextCharacter;
            const auto position = pNextCharacter - pText;
            const auto characterUCS4 = SkUTF16_NextUnichar(reinterpret_cast<const uint16_t**>(&pNextCharacter));
            
            // First of all check previous font if it contains this character
            auto font = pTextPaint ? pTextPaint->paint.getTypeface() : nullptr;
            if (font)
            {
                SkPaint paint;
                paint.setTextEncoding(SkPaint::kUTF32_TextEncoding);
                paint.setTypeface(font);
                if (!paint.containsText(&characterUCS4, sizeof(uint32_t)))
                    font = nullptr;
#if OSMAND_LOG_CHARACTERS_FONT
                else
                {
                    SkString fontName;
                    font->getFamilyName(&fontName);

                    LogPrintf(LogSeverityLevel::Warning,
                        "UCS4 character 0x%08x (%u) has been found in '%s' font (reused)",
                        characterUCS4,
                        characterUCS4,
                        fontName.c_str());
                }
#endif // OSMAND_LOG_CHARACTERS_FONT
            }
            if (!font)
            {
                font = owner->fontFinder->findFontForCharacterUCS4(characterUCS4, fontStyle);

#if OSMAND_LOG_CHARACTERS_WITHOUT_FONT
                if (!font)
                {
                    LogPrintf(LogSeverityLevel::Warning,
                        "UCS4 character 0x%08x (%u) has not been found in any font",
                        characterUCS4,
                        characterUCS4);
                }
#endif // OSMAND_LOG_CHARACTERS_WITHOUT_FONT

#if OSMAND_LOG_CHARACTERS_FONT
                if (font)
                {
                    SkString fontName;
                    font->getFamilyName(&fontName);

                    LogPrintf(LogSeverityLevel::Warning,
                        "UCS4 character 0x%08x (%u) has been found in '%s' font",
                        characterUCS4,
                        characterUCS4,
                        fontName.c_str());
                }
#endif // OSMAND_LOG_CHARACTERS_FONT
            }

            if (pTextPaint == nullptr || pTextPaint->paint.getTypeface() != font)
            {
                linePaint.textPaints.push_back(qMove(TextPaint()));
                pTextPaint = &linePaint.textPaints.last();

                pTextPaint->text = QStringRef(lineRef.string(), position, 1);
                pTextPaint->paint = paint;
                pTextPaint->paint.setTypeface(font);

                SkPaint::FontMetrics metrics;
                pTextPaint->height = paint.getFontMetrics(&metrics);
                linePaint.maxFontHeight = qMax(linePaint.maxFontHeight, pTextPaint->height);
                linePaint.minFontHeight = qMin(linePaint.minFontHeight, pTextPaint->height);
                linePaint.maxFontLineSpacing = qMax(linePaint.maxFontLineSpacing, metrics.fLeading);
                linePaint.minFontLineSpacing = qMin(linePaint.minFontLineSpacing, metrics.fLeading);
                linePaint.maxFontTop = qMax(linePaint.maxFontTop, -metrics.fTop);
                linePaint.minFontTop = qMin(linePaint.minFontTop, -metrics.fTop);
                linePaint.maxFontBottom = qMax(linePaint.maxFontBottom, metrics.fBottom);
                linePaint.minFontBottom = qMin(linePaint.minFontBottom, metrics.fBottom);

                if (style.bold && (!font || (font && font->fontStyle().weight() <= SkFontStyle::kNormal_Weight)))
                    pTextPaint->paint.setFakeBoldText(true);
            }
            else
            {
                pTextPaint->text = QStringRef(lineRef.string(), pTextPaint->text.position(), pTextPaint->text.size() + 1);
            }
        }

        linePaints.push_back(qMove(linePaint));
    }

    return linePaints;
}

void OsmAnd::TextRasterizer_P::measureText(QVector<LinePaint>& paints, SkScalar& outMaxLineWidth) const
{
    outMaxLineWidth = 0;

    for (auto& linePaint : paints)
    {
        linePaint.maxBoundsTop = 0;
        linePaint.minBoundsTop = std::numeric_limits<SkScalar>::max();
        linePaint.width = 0;

        for (auto& textPaint : linePaint.textPaints)
        {
            textPaint.paint.measureText(
                textPaint.text.constData(),
                textPaint.text.length()*sizeof(QChar),
                &textPaint.bounds);

            textPaint.width = textPaint.bounds.width();

            linePaint.maxBoundsTop = qMax(linePaint.maxBoundsTop, -textPaint.bounds.top());
            linePaint.minBoundsTop = qMin(linePaint.minBoundsTop, -textPaint.bounds.top());
            linePaint.width += textPaint.width;
        }

        outMaxLineWidth = qMax(outMaxLineWidth, linePaint.width);
    }
}

void OsmAnd::TextRasterizer_P::measureGlyphs(const QVector<LinePaint>& paints, QVector<SkScalar>& outGlyphWidths) const
{
    for (const auto& linePaint : constOf(paints))
    {
        for (const auto& textPaint : constOf(linePaint.textPaints))
        {
            const auto glyphsCount = textPaint.paint.countText(
                textPaint.text.constData(),
                textPaint.text.length()*sizeof(QChar));
            const auto previousSize = outGlyphWidths.size();
            outGlyphWidths.resize(previousSize + glyphsCount);
            const auto pWidth = outGlyphWidths.data() + previousSize;
            textPaint.paint.getTextWidths(
                textPaint.text.constData(),
                textPaint.text.length()*sizeof(QChar),
                pWidth);

            *pWidth += -textPaint.bounds.left();
        }
    }
}

SkPaint OsmAnd::TextRasterizer_P::getHaloPaint(const SkPaint& paint, const Style& style) const
{
    auto haloPaint = paint;
    haloPaint.setStyle(SkPaint::kStroke_Style);
    haloPaint.setColor(style.haloColor.toSkColor());
    haloPaint.setStrokeWidth(style.haloRadius);

    return haloPaint;
}

void OsmAnd::TextRasterizer_P::measureHalo(const Style& style, QVector<LinePaint>& paints) const
{
    for (auto& linePaint : paints)
    {
        linePaint.maxBoundsTop = 0;
        linePaint.minBoundsTop = std::numeric_limits<SkScalar>::max();

        for (auto& textPaint : linePaint.textPaints)
        {
            const auto haloPaint = getHaloPaint(textPaint.paint, style);

            SkPaint::FontMetrics metrics;
            textPaint.height = haloPaint.getFontMetrics(&metrics);
            linePaint.maxFontHeight = qMax(linePaint.maxFontHeight, textPaint.height);
            linePaint.minFontHeight = qMin(linePaint.minFontHeight, textPaint.height);
            linePaint.maxFontLineSpacing = qMax(linePaint.maxFontLineSpacing, metrics.fLeading);
            linePaint.minFontLineSpacing = qMin(linePaint.minFontLineSpacing, metrics.fLeading);
            linePaint.maxFontTop = qMax(linePaint.maxFontTop, -metrics.fTop);
            linePaint.minFontTop = qMin(linePaint.minFontTop, -metrics.fTop);
            linePaint.maxFontBottom = qMax(linePaint.maxFontBottom, metrics.fBottom);
            linePaint.minFontBottom = qMin(linePaint.minFontBottom, metrics.fBottom);

            SkRect haloBounds;
            haloPaint.measureText(
                textPaint.text.constData(),
                textPaint.text.length()*sizeof(QChar),
                &haloBounds);
            textPaint.bounds.join(haloBounds);

            linePaint.maxBoundsTop = qMax(linePaint.maxBoundsTop, -textPaint.bounds.top());
            linePaint.minBoundsTop = qMin(linePaint.minBoundsTop, -textPaint.bounds.top());
        }
    }
}

void OsmAnd::TextRasterizer_P::measureHaloGlyphs(
    const Style& style,
    const QVector<LinePaint>& paints,
    QVector<SkScalar>& outGlyphWidths) const
{
    for (const auto& linePaint : constOf(paints))
    {
        for (const auto& textPaint : constOf(linePaint.textPaints))
        {
            const auto haloPaint = getHaloPaint(textPaint.paint, style);

            const auto glyphsCount = haloPaint.countText(
                textPaint.text.constData(),
                textPaint.text.length()*sizeof(QChar));
            const auto previousSize = outGlyphWidths.size();
            outGlyphWidths.resize(previousSize + glyphsCount);
            const auto pWidth = outGlyphWidths.data() + previousSize;
            haloPaint.getTextWidths(
                textPaint.text.constData(),
                textPaint.text.length()*sizeof(QChar),
                pWidth);

            *pWidth += -textPaint.bounds.left();
        }
    }
}

SkRect OsmAnd::TextRasterizer_P::positionText(
    QVector<LinePaint>& paints,
    const SkScalar maxLineWidth,
    const Style::TextAlignment textAlignment) const
{
    auto textArea = SkRect::MakeEmpty();

    SkScalar verticalOffset = 0;
    for (auto& linePaint : paints)
    {
        SkScalar horizontalOffset = 0;
        const auto widthDelta = maxLineWidth - linePaint.width;
        switch (textAlignment)
        {
            case Style::TextAlignment::Center:
                horizontalOffset += widthDelta / 2.0f;
                break;

            case Style::TextAlignment::Right:
                horizontalOffset += widthDelta;
                break;

            case Style::TextAlignment::Left:
            default:
                // Do nothing here
                break;
        }

        for (auto& textPaint : linePaint.textPaints)
        {
            textPaint.positionedBounds = textPaint.bounds;

            // Position horizontally
            textPaint.positionedBounds.offset(-2.0f*textPaint.bounds.left(), 0);
            textPaint.positionedBounds.offset(horizontalOffset, 0);
            horizontalOffset += textPaint.width;

            // Position vertically
            textPaint.positionedBounds.offset(0, -2.0f*textPaint.bounds.top());
            textPaint.positionedBounds.offset(0, linePaint.maxBoundsTop + textPaint.bounds.top());
            textPaint.positionedBounds.offset(0, verticalOffset);

            // Include into text area
            textArea.join(textPaint.positionedBounds);
        }

        verticalOffset += linePaint.maxFontHeight;

        //// Calculate text area and move bounds vertically
        //auto textArea = linesNormalizedBounds.first();
        //auto linesHeightSum = textArea.height();
        //auto citPrevLineBounds = linesBounds.cbegin();
        //auto citLineBounds = citPrevLineBounds + 1;
        //for (auto itNormalizedLineBounds = linesNormalizedBounds.begin() + 1, itEnd = linesNormalizedBounds.end();
        //    itNormalizedLineBounds != itEnd;
        //    ++itNormalizedLineBounds, citPrevLineBounds = citLineBounds, ++citLineBounds)
        //{
        //    auto& lineNormalizedBounds = *itNormalizedLineBounds;
        //    const auto& prevLineBounds = *citPrevLineBounds;
        //    const auto& lineBounds = *citLineBounds;

        //    // Include gap between previous line and it's font-end
        //    const auto extraPrevGapHeight = qMax(0.0f, fontMaxBottom - prevLineBounds.fBottom);
        //    textArea.fBottom += extraPrevGapHeight;
        //    linesHeightSum += extraPrevGapHeight;

        //    // Include line spacing
        //    textArea.fBottom += lineSpacing;
        //    linesHeightSum += lineSpacing;

        //    // Include gap between current line and it's font-start
        //    const auto extraGapHeight = qMax(0.0f, fontMaxTop - (-lineBounds.fTop));
        //    textArea.fBottom += extraGapHeight;
        //    linesHeightSum += extraGapHeight;

        //    // Move current line baseline
        //    lineNormalizedBounds.offset(0.0f, linesHeightSum);

        //    // Include height of current line
        //    const auto& lineHeight = lineNormalizedBounds.height();
        //    textArea.fBottom += lineHeight;
        //    linesHeightSum += lineHeight;

        //    // This will expand left-right bounds to get proper area width
        //    textArea.fLeft = qMin(textArea.fLeft, lineNormalizedBounds.fLeft);
        //    textArea.fRight = qMax(textArea.fRight, lineNormalizedBounds.fRight);
        //}

    }

    return textArea;
}

std::shared_ptr<SkBitmap> OsmAnd::TextRasterizer_P::rasterize(
    const QString& text,
    const Style& style,
    QVector<SkScalar>* const outGlyphWidths,
    float* const outExtraTopSpace,
    float* const outExtraBottomSpace,
    float* const outLineSpacing) const
{
    std::shared_ptr<SkBitmap> bitmap(new SkBitmap());
    const bool ok = rasterize(
        *bitmap,
        text,
        style,
        outGlyphWidths,
        outExtraTopSpace,
        outExtraBottomSpace,
        outLineSpacing);
    if (!ok)
        return nullptr;
    return bitmap;
}

bool OsmAnd::TextRasterizer_P::rasterize(
    SkBitmap& targetBitmap,
    const QString& text_,
    const Style& style,
    QVector<SkScalar>* const outGlyphWidths,
    float* const outExtraTopSpace,
    float* const outExtraBottomSpace,
    float* const outLineSpacing) const
{
    // Prepare text and break by lines
    const auto text = ICU::convertToVisualOrder(text_);
    const auto lineRefs = style.wrapWidth > 0
        ? ICU::getTextWrappingRefs(text, style.wrapWidth)
        : (QVector<QStringRef>() << QStringRef(&text));

    // Obtain paints from lines and style
    auto paints = evaluatePaints(lineRefs, style);

    // Measure text
    SkScalar maxLineWidthInPixels = 0;
    measureText(paints, maxLineWidthInPixels);

    // Measure glyphs (if requested and there's no halo)
    if (outGlyphWidths && style.haloRadius == 0)
        measureGlyphs(paints, *outGlyphWidths);

    // Process halo if exists
    if (style.haloRadius > 0)
    {
        measureHalo(style, paints);

        if (outGlyphWidths)
            measureHaloGlyphs(style, paints, *outGlyphWidths);
    }

    // Set output line spacing
    if (outLineSpacing)
    {
        float lineSpacing = 0.0f;
        for (const auto& linePaint : constOf(paints))
            lineSpacing = qMax(lineSpacing, linePaint.maxFontLineSpacing);

        *outLineSpacing = lineSpacing;
    }

    // Calculate extra top and bottom space
    if (outExtraTopSpace)
    {
        SkScalar maxTop = 0;
        for (const auto& linePaint : constOf(paints))
            maxTop = qMax(maxTop, linePaint.maxFontTop);

        *outExtraTopSpace = qMax(0.0f, maxTop - paints.first().maxFontTop);
    }
    if (outExtraBottomSpace)
    {
        SkScalar maxBottom = 0;
        for (const auto& linePaint : constOf(paints))
            maxBottom = qMax(maxBottom, linePaint.maxFontBottom);

        *outExtraBottomSpace = qMax(0.0f, maxBottom - paints.last().maxFontBottom);
    }

    // Position text horizontally and vertically
    const auto textArea = positionText(paints, maxLineWidthInPixels, style.textAlignment);
    
    // Calculate bitmap size
    auto bitmapWidth = qCeil(textArea.width());
    auto bitmapHeight = qCeil(textArea.height());
    if (style.backgroundBitmap)
    {
        // Clear extra spacing
        if (outExtraTopSpace)
            *outExtraTopSpace = 0.0f;
        if (outExtraBottomSpace)
            *outExtraBottomSpace = 0.0f;

        // Enlarge bitmap if shield is larger than text
        bitmapWidth = qMax(bitmapWidth, style.backgroundBitmap->width());
        bitmapHeight = qMax(bitmapHeight, style.backgroundBitmap->height());

        // Shift text area to proper position in a larger
        const auto offset = SkPoint::Make(
            (bitmapWidth - qCeil(textArea.width())) / 2.0f,
            (bitmapHeight - qCeil(textArea.height())) / 2.0f);
        for (auto& linePaint : paints)
        {
            for (auto& textPaint : linePaint.textPaints)
                textPaint.positionedBounds.offset(offset);
        }
    }

    // Check if bitmap size was successfully calculated
    if (bitmapWidth <= 0 || bitmapHeight <= 0)
    {
        LogPrintf(LogSeverityLevel::Error,
            "Failed to rasterize text '%s': resulting bitmap size %dx%d is invalid",
            qPrintable(text),
            bitmapWidth,
            bitmapHeight);
        return false;
    }

    // Create a bitmap that will be hold entire symbol (if target is empty)
    if (targetBitmap.isNull())
    {
        if (!targetBitmap.tryAllocPixels(SkImageInfo::MakeN32Premul(bitmapWidth, bitmapHeight)))
        {
            LogPrintf(LogSeverityLevel::Error,
                "Failed to allocate bitmap of size %dx%d",
                qPrintable(text),
                bitmapWidth,
                bitmapHeight);
            return false;
        }

        targetBitmap.eraseColor(SK_ColorTRANSPARENT);
    }
    SkBitmapDevice target(targetBitmap);
    SkCanvas canvas(&target);

    // If there is background this text, rasterize it also
    if (style.backgroundBitmap)
    {
        canvas.drawBitmap(*style.backgroundBitmap,
            (bitmapWidth - style.backgroundBitmap->width()) / 2.0f,
            (bitmapHeight - style.backgroundBitmap->height()) / 2.0f,
            nullptr);
    }

    // Rasterize text halo first (if enabled)
    if (style.haloRadius > 0)
    {
        for (const auto& linePaint : paints)
        {
            for (const auto& textPaint : linePaint.textPaints)
            {
                const auto haloPaint = getHaloPaint(textPaint.paint, style);

                canvas.drawText(
                    textPaint.text.constData(), textPaint.text.length()*sizeof(QChar),
                    textPaint.positionedBounds.left(), textPaint.positionedBounds.top(),
                    haloPaint);
            }
        }
    }

    // Rasterize text itself
    for (const auto& linePaint : paints)
    {
        for (const auto& textPaint : linePaint.textPaints)
        {
            canvas.drawText(
                textPaint.text.constData(), textPaint.text.length()*sizeof(QChar),
                textPaint.positionedBounds.left(), textPaint.positionedBounds.top(),
                textPaint.paint);
        }
    }

    canvas.flush();

    return true;
}
