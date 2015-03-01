#ifndef PNGRENAME_H
#define PNGRENAME_H

#define PNG_RENAME(name) osmand_##name

#define png_compress_IDAT                               PNG_RENAME(png_compress_IDAT)
#define png_do_write_interlace                          PNG_RENAME(png_do_write_interlace)
#define png_free_buffer_list                            PNG_RENAME(png_free_buffer_list)
#define png_save_uint_16                                PNG_RENAME(png_save_uint_16)
#define png_save_uint_32                                PNG_RENAME(png_save_uint_32)
#define png_write_IEND                                  PNG_RENAME(png_write_IEND)
#define png_write_IHDR                                  PNG_RENAME(png_write_IHDR)
#define png_write_PLTE                                  PNG_RENAME(png_write_PLTE)
#define png_write_bKGD                                  PNG_RENAME(png_write_bKGD)
#define png_write_cHRM_fixed                            PNG_RENAME(png_write_cHRM_fixed)
#define png_write_chunk                                 PNG_RENAME(png_write_chunk)
#define png_write_chunk_data                            PNG_RENAME(png_write_chunk_data)
#define png_write_chunk_end                             PNG_RENAME(png_write_chunk_end)
#define png_write_chunk_start                           PNG_RENAME(png_write_chunk_start)
#define png_write_find_filter                           PNG_RENAME(png_write_find_filter)
#define png_write_finish_row                            PNG_RENAME(png_write_finish_row)
#define png_write_gAMA_fixed                            PNG_RENAME(png_write_gAMA_fixed)
#define png_write_hIST                                  PNG_RENAME(png_write_hIST)
#define png_write_iCCP                                  PNG_RENAME(png_write_iCCP)
#define png_write_iTXt                                  PNG_RENAME(png_write_iTXt)
#define png_write_oFFs                                  PNG_RENAME(png_write_oFFs)
#define png_write_pCAL                                  PNG_RENAME(png_write_pCAL)
#define png_write_pHYs                                  PNG_RENAME(png_write_pHYs)
#define png_write_sBIT                                  PNG_RENAME(png_write_sBIT)
#define png_write_sCAL_s                                PNG_RENAME(png_write_sCAL_s)
#define png_write_sPLT                                  PNG_RENAME(png_write_sPLT)
#define png_write_sRGB                                  PNG_RENAME(png_write_sRGB)
#define png_write_sig                                   PNG_RENAME(png_write_sig)
#define png_write_start_row                             PNG_RENAME(png_write_start_row)
#define png_write_tEXt                                  PNG_RENAME(png_write_tEXt)
#define png_write_tIME                                  PNG_RENAME(png_write_tIME)
#define png_write_tRNS                                  PNG_RENAME(png_write_tRNS)
#define png_write_zTXt                                  PNG_RENAME(png_write_zTXt)
#define png_do_write_transformations                    PNG_RENAME(png_do_write_transformations)
#define png_convert_from_struct_tm                      PNG_RENAME(png_convert_from_struct_tm)
#define png_convert_from_time_t                         PNG_RENAME(png_convert_from_time_t)
#define png_create_write_struct                         PNG_RENAME(png_create_write_struct)
#define png_create_write_struct_2                       PNG_RENAME(png_create_write_struct_2)
#define png_destroy_write_struct                        PNG_RENAME(png_destroy_write_struct)
#define png_image_write_to_file                         PNG_RENAME(png_image_write_to_file)
#define png_image_write_to_stdio                        PNG_RENAME(png_image_write_to_stdio)
#define png_set_compression_level                       PNG_RENAME(png_set_compression_level)
#define png_set_compression_mem_level                   PNG_RENAME(png_set_compression_mem_level)
#define png_set_compression_method                      PNG_RENAME(png_set_compression_method)
#define png_set_compression_strategy                    PNG_RENAME(png_set_compression_strategy)
#define png_set_compression_window_bits                 PNG_RENAME(png_set_compression_window_bits)
#define png_set_filter                                  PNG_RENAME(png_set_filter)
#define png_set_filter_heuristics                       PNG_RENAME(png_set_filter_heuristics)
#define png_set_filter_heuristics_fixed                 PNG_RENAME(png_set_filter_heuristics_fixed)
#define png_set_flush                                   PNG_RENAME(png_set_flush)
#define png_set_text_compression_level                  PNG_RENAME(png_set_text_compression_level)
#define png_set_text_compression_mem_level              PNG_RENAME(png_set_text_compression_mem_level)
#define png_set_text_compression_method                 PNG_RENAME(png_set_text_compression_method)
#define png_set_text_compression_strategy               PNG_RENAME(png_set_text_compression_strategy)
#define png_set_text_compression_window_bits            PNG_RENAME(png_set_text_compression_window_bits)
#define png_set_write_status_fn                         PNG_RENAME(png_set_write_status_fn)
#define png_set_write_user_transform_fn                 PNG_RENAME(png_set_write_user_transform_fn)
#define png_write_end                                   PNG_RENAME(png_write_end)
#define png_write_flush                                 PNG_RENAME(png_write_flush)
#define png_write_image                                 PNG_RENAME(png_write_image)
#define png_write_info                                  PNG_RENAME(png_write_info)
#define png_write_info_before_PLTE                      PNG_RENAME(png_write_info_before_PLTE)
#define png_write_png                                   PNG_RENAME(png_write_png)
#define png_write_row                                   PNG_RENAME(png_write_row)
#define png_write_rows                                  PNG_RENAME(png_write_rows)
#define png_default_flush                               PNG_RENAME(png_default_flush)
#define png_default_write_data                          PNG_RENAME(png_default_write_data)
#define png_flush                                       PNG_RENAME(png_flush)
#define png_set_write_fn                                PNG_RENAME(png_set_write_fn)
#define png_write_data                                  PNG_RENAME(png_write_data)
#define png_do_bgr                                      PNG_RENAME(png_do_bgr)
#define png_do_check_palette_indexes                    PNG_RENAME(png_do_check_palette_indexes)
#define png_do_invert                                   PNG_RENAME(png_do_invert)
#define png_do_packswap                                 PNG_RENAME(png_do_packswap)
#define png_do_strip_channel                            PNG_RENAME(png_do_strip_channel)
#define png_do_swap                                     PNG_RENAME(png_do_swap)
#define png_get_current_pass_number                     PNG_RENAME(png_get_current_pass_number)
#define png_get_current_row_number                      PNG_RENAME(png_get_current_row_number)
#define png_get_user_transform_ptr                      PNG_RENAME(png_get_user_transform_ptr)
#define png_set_add_alpha                               PNG_RENAME(png_set_add_alpha)
#define png_set_bgr                                     PNG_RENAME(png_set_bgr)
#define png_set_filler                                  PNG_RENAME(png_set_filler)
#define png_set_interlace_handling                      PNG_RENAME(png_set_interlace_handling)
#define png_set_invert_alpha                            PNG_RENAME(png_set_invert_alpha)
#define png_set_invert_mono                             PNG_RENAME(png_set_invert_mono)
#define png_set_packing                                 PNG_RENAME(png_set_packing)
#define png_set_packswap                                PNG_RENAME(png_set_packswap)
#define png_set_shift                                   PNG_RENAME(png_set_shift)
#define png_set_swap                                    PNG_RENAME(png_set_swap)
#define png_set_swap_alpha                              PNG_RENAME(png_set_swap_alpha)
#define png_set_user_transform_info                     PNG_RENAME(png_set_user_transform_info)
#define png_permit_mng_features                         PNG_RENAME(png_permit_mng_features)
#define png_set_IHDR                                    PNG_RENAME(png_set_IHDR)
#define png_set_PLTE                                    PNG_RENAME(png_set_PLTE)
#define png_set_bKGD                                    PNG_RENAME(png_set_bKGD)
#define png_set_benign_errors                           PNG_RENAME(png_set_benign_errors)
#define png_set_cHRM                                    PNG_RENAME(png_set_cHRM)
#define png_set_cHRM_XYZ                                PNG_RENAME(png_set_cHRM_XYZ)
#define png_set_cHRM_XYZ_fixed                          PNG_RENAME(png_set_cHRM_XYZ_fixed)
#define png_set_cHRM_fixed                              PNG_RENAME(png_set_cHRM_fixed)
#define png_set_check_for_invalid_index                 PNG_RENAME(png_set_check_for_invalid_index)
#define png_set_chunk_cache_max                         PNG_RENAME(png_set_chunk_cache_max)
#define png_set_chunk_malloc_max                        PNG_RENAME(png_set_chunk_malloc_max)
#define png_set_compression_buffer_size                 PNG_RENAME(png_set_compression_buffer_size)
#define png_set_gAMA                                    PNG_RENAME(png_set_gAMA)
#define png_set_gAMA_fixed                              PNG_RENAME(png_set_gAMA_fixed)
#define png_set_hIST                                    PNG_RENAME(png_set_hIST)
#define png_set_iCCP                                    PNG_RENAME(png_set_iCCP)
#define png_set_invalid                                 PNG_RENAME(png_set_invalid)
#define png_set_keep_unknown_chunks                     PNG_RENAME(png_set_keep_unknown_chunks)
#define png_set_oFFs                                    PNG_RENAME(png_set_oFFs)
#define png_set_pCAL                                    PNG_RENAME(png_set_pCAL)
#define png_set_pHYs                                    PNG_RENAME(png_set_pHYs)
#define png_set_read_user_chunk_fn                      PNG_RENAME(png_set_read_user_chunk_fn)
#define png_set_rows                                    PNG_RENAME(png_set_rows)
#define png_set_sBIT                                    PNG_RENAME(png_set_sBIT)
#define png_set_sCAL                                    PNG_RENAME(png_set_sCAL)
#define png_set_sCAL_fixed                              PNG_RENAME(png_set_sCAL_fixed)
#define png_set_sCAL_s                                  PNG_RENAME(png_set_sCAL_s)
#define png_set_sPLT                                    PNG_RENAME(png_set_sPLT)
#define png_set_sRGB                                    PNG_RENAME(png_set_sRGB)
#define png_set_sRGB_gAMA_and_cHRM                      PNG_RENAME(png_set_sRGB_gAMA_and_cHRM)
#define png_set_tIME                                    PNG_RENAME(png_set_tIME)
#define png_set_tRNS                                    PNG_RENAME(png_set_tRNS)
#define png_set_text                                    PNG_RENAME(png_set_text)
#define png_set_text_2                                  PNG_RENAME(png_set_text_2)
#define png_set_unknown_chunk_location                  PNG_RENAME(png_set_unknown_chunk_location)
#define png_set_unknown_chunks                          PNG_RENAME(png_set_unknown_chunks)
#define png_set_user_limits                             PNG_RENAME(png_set_user_limits)
#define png_check_chunk_name                            PNG_RENAME(png_check_chunk_name)
#define png_combine_row                                 PNG_RENAME(png_combine_row)
#define png_crc_error                                   PNG_RENAME(png_crc_error)
#define png_crc_finish                                  PNG_RENAME(png_crc_finish)
#define png_crc_read                                    PNG_RENAME(png_crc_read)
#define png_do_read_interlace                           PNG_RENAME(png_do_read_interlace)
#define png_get_int_32                                  PNG_RENAME(png_get_int_32)
#define png_get_uint_16                                 PNG_RENAME(png_get_uint_16)
#define png_get_uint_31                                 PNG_RENAME(png_get_uint_31)
#define png_get_uint_32                                 PNG_RENAME(png_get_uint_32)
#define png_handle_IEND                                 PNG_RENAME(png_handle_IEND)
#define png_handle_IHDR                                 PNG_RENAME(png_handle_IHDR)
#define png_handle_PLTE                                 PNG_RENAME(png_handle_PLTE)
#define png_handle_bKGD                                 PNG_RENAME(png_handle_bKGD)
#define png_handle_cHRM                                 PNG_RENAME(png_handle_cHRM)
#define png_handle_gAMA                                 PNG_RENAME(png_handle_gAMA)
#define png_handle_hIST                                 PNG_RENAME(png_handle_hIST)
#define png_handle_iCCP                                 PNG_RENAME(png_handle_iCCP)
#define png_handle_iTXt                                 PNG_RENAME(png_handle_iTXt)
#define png_handle_oFFs                                 PNG_RENAME(png_handle_oFFs)
#define png_handle_pCAL                                 PNG_RENAME(png_handle_pCAL)
#define png_handle_pHYs                                 PNG_RENAME(png_handle_pHYs)
#define png_handle_sBIT                                 PNG_RENAME(png_handle_sBIT)
#define png_handle_sCAL                                 PNG_RENAME(png_handle_sCAL)
#define png_handle_sPLT                                 PNG_RENAME(png_handle_sPLT)
#define png_handle_sRGB                                 PNG_RENAME(png_handle_sRGB)
#define png_handle_tEXt                                 PNG_RENAME(png_handle_tEXt)
#define png_handle_tIME                                 PNG_RENAME(png_handle_tIME)
#define png_handle_tRNS                                 PNG_RENAME(png_handle_tRNS)
#define png_handle_unknown                              PNG_RENAME(png_handle_unknown)
#define png_handle_zTXt                                 PNG_RENAME(png_handle_zTXt)
#define png_read_IDAT_data                              PNG_RENAME(png_read_IDAT_data)
#define png_read_chunk_header                           PNG_RENAME(png_read_chunk_header)
#define png_read_filter_row                             PNG_RENAME(png_read_filter_row)
#define png_read_finish_IDAT                            PNG_RENAME(png_read_finish_IDAT)
#define png_read_finish_row                             PNG_RENAME(png_read_finish_row)
#define png_read_sig                                    PNG_RENAME(png_read_sig)
#define png_read_start_row                              PNG_RENAME(png_read_start_row)
#define png_do_read_transformations                     PNG_RENAME(png_do_read_transformations)
#define png_init_read_transformations                   PNG_RENAME(png_init_read_transformations)
#define png_read_transform_info                         PNG_RENAME(png_read_transform_info)
#define png_set_alpha_mode                              PNG_RENAME(png_set_alpha_mode)
#define png_set_alpha_mode_fixed                        PNG_RENAME(png_set_alpha_mode_fixed)
#define png_set_background                              PNG_RENAME(png_set_background)
#define png_set_background_fixed                        PNG_RENAME(png_set_background_fixed)
#define png_set_crc_action                              PNG_RENAME(png_set_crc_action)
#define png_set_expand                                  PNG_RENAME(png_set_expand)
#define png_set_expand_16                               PNG_RENAME(png_set_expand_16)
#define png_set_expand_gray_1_2_4_to_8                  PNG_RENAME(png_set_expand_gray_1_2_4_to_8)
#define png_set_gamma                                   PNG_RENAME(png_set_gamma)
#define png_set_gamma_fixed                             PNG_RENAME(png_set_gamma_fixed)
#define png_set_gray_to_rgb                             PNG_RENAME(png_set_gray_to_rgb)
#define png_set_palette_to_rgb                          PNG_RENAME(png_set_palette_to_rgb)
#define png_set_quantize                                PNG_RENAME(png_set_quantize)
#define png_set_read_user_transform_fn                  PNG_RENAME(png_set_read_user_transform_fn)
#define png_set_rgb_to_gray                             PNG_RENAME(png_set_rgb_to_gray)
#define png_set_rgb_to_gray_fixed                       PNG_RENAME(png_set_rgb_to_gray_fixed)
#define png_set_scale_16                                PNG_RENAME(png_set_scale_16)
#define png_set_strip_16                                PNG_RENAME(png_set_strip_16)
#define png_set_strip_alpha                             PNG_RENAME(png_set_strip_alpha)
#define png_set_tRNS_to_alpha                           PNG_RENAME(png_set_tRNS_to_alpha)
#define png_default_read_data                           PNG_RENAME(png_default_read_data)
#define png_read_data                                   PNG_RENAME(png_read_data)
#define png_set_read_fn                                 PNG_RENAME(png_set_read_fn)
#define png_create_read_struct                          PNG_RENAME(png_create_read_struct)
#define png_create_read_struct_2                        PNG_RENAME(png_create_read_struct_2)
#define png_destroy_read_struct                         PNG_RENAME(png_destroy_read_struct)
#define png_image_begin_read_from_file                  PNG_RENAME(png_image_begin_read_from_file)
#define png_image_begin_read_from_memory                PNG_RENAME(png_image_begin_read_from_memory)
#define png_image_begin_read_from_stdio                 PNG_RENAME(png_image_begin_read_from_stdio)
#define png_image_finish_read                           PNG_RENAME(png_image_finish_read)
#define png_read_end                                    PNG_RENAME(png_read_end)
#define png_read_image                                  PNG_RENAME(png_read_image)
#define png_read_info                                   PNG_RENAME(png_read_info)
#define png_read_png                                    PNG_RENAME(png_read_png)
#define png_read_row                                    PNG_RENAME(png_read_row)
#define png_read_rows                                   PNG_RENAME(png_read_rows)
#define png_read_update_info                            PNG_RENAME(png_read_update_info)
#define png_set_read_status_fn                          PNG_RENAME(png_set_read_status_fn)
#define png_start_read_image                            PNG_RENAME(png_start_read_image)
#define png_get_progressive_ptr                         PNG_RENAME(png_get_progressive_ptr)
#define png_process_IDAT_data                           PNG_RENAME(png_process_IDAT_data)
#define png_process_data                                PNG_RENAME(png_process_data)
#define png_process_data_pause                          PNG_RENAME(png_process_data_pause)
#define png_process_data_skip                           PNG_RENAME(png_process_data_skip)
#define png_process_some_data                           PNG_RENAME(png_process_some_data)
#define png_progressive_combine_row                     PNG_RENAME(png_progressive_combine_row)
#define png_push_crc_finish                             PNG_RENAME(png_push_crc_finish)
#define png_push_crc_skip                               PNG_RENAME(png_push_crc_skip)
#define png_push_fill_buffer                            PNG_RENAME(png_push_fill_buffer)
#define png_push_have_end                               PNG_RENAME(png_push_have_end)
#define png_push_have_info                              PNG_RENAME(png_push_have_info)
#define png_push_have_row                               PNG_RENAME(png_push_have_row)
#define png_push_process_row                            PNG_RENAME(png_push_process_row)
#define png_push_read_IDAT                              PNG_RENAME(png_push_read_IDAT)
#define png_push_read_chunk                             PNG_RENAME(png_push_read_chunk)
#define png_push_read_sig                               PNG_RENAME(png_push_read_sig)
#define png_push_restore_buffer                         PNG_RENAME(png_push_restore_buffer)
#define png_push_save_buffer                            PNG_RENAME(png_push_save_buffer)
#define png_read_push_finish_row                        PNG_RENAME(png_read_push_finish_row)
#define png_set_progressive_read_fn                     PNG_RENAME(png_set_progressive_read_fn)
#define png_calloc                                      PNG_RENAME(png_calloc)
#define png_destroy_png_struct                          PNG_RENAME(png_destroy_png_struct)
#define png_free                                        PNG_RENAME(png_free)
#define png_free_default                                PNG_RENAME(png_free_default)
#define png_get_mem_ptr                                 PNG_RENAME(png_get_mem_ptr)
#define png_malloc                                      PNG_RENAME(png_malloc)
#define png_malloc_array                                PNG_RENAME(png_malloc_array)
#define png_malloc_base                                 PNG_RENAME(png_malloc_base)
#define png_malloc_default                              PNG_RENAME(png_malloc_default)
#define png_malloc_warn                                 PNG_RENAME(png_malloc_warn)
#define png_realloc_array                               PNG_RENAME(png_realloc_array)
#define png_set_mem_fn                                  PNG_RENAME(png_set_mem_fn)
#define png_get_IHDR                                    PNG_RENAME(png_get_IHDR)
#define png_get_PLTE                                    PNG_RENAME(png_get_PLTE)
#define png_get_bKGD                                    PNG_RENAME(png_get_bKGD)
#define png_get_bit_depth                               PNG_RENAME(png_get_bit_depth)
#define png_get_cHRM                                    PNG_RENAME(png_get_cHRM)
#define png_get_cHRM_XYZ                                PNG_RENAME(png_get_cHRM_XYZ)
#define png_get_cHRM_XYZ_fixed                          PNG_RENAME(png_get_cHRM_XYZ_fixed)
#define png_get_cHRM_fixed                              PNG_RENAME(png_get_cHRM_fixed)
#define png_get_channels                                PNG_RENAME(png_get_channels)
#define png_get_chunk_cache_max                         PNG_RENAME(png_get_chunk_cache_max)
#define png_get_chunk_malloc_max                        PNG_RENAME(png_get_chunk_malloc_max)
#define png_get_color_type                              PNG_RENAME(png_get_color_type)
#define png_get_compression_buffer_size                 PNG_RENAME(png_get_compression_buffer_size)
#define png_get_compression_type                        PNG_RENAME(png_get_compression_type)
#define png_get_filter_type                             PNG_RENAME(png_get_filter_type)
#define png_get_gAMA                                    PNG_RENAME(png_get_gAMA)
#define png_get_gAMA_fixed                              PNG_RENAME(png_get_gAMA_fixed)
#define png_get_hIST                                    PNG_RENAME(png_get_hIST)
#define png_get_iCCP                                    PNG_RENAME(png_get_iCCP)
#define png_get_image_height                            PNG_RENAME(png_get_image_height)
#define png_get_image_width                             PNG_RENAME(png_get_image_width)
#define png_get_interlace_type                          PNG_RENAME(png_get_interlace_type)
#define png_get_io_chunk_type                           PNG_RENAME(png_get_io_chunk_type)
#define png_get_io_state                                PNG_RENAME(png_get_io_state)
#define png_get_oFFs                                    PNG_RENAME(png_get_oFFs)
#define png_get_pCAL                                    PNG_RENAME(png_get_pCAL)
#define png_get_pHYs                                    PNG_RENAME(png_get_pHYs)
#define png_get_pHYs_dpi                                PNG_RENAME(png_get_pHYs_dpi)
#define png_get_palette_max                             PNG_RENAME(png_get_palette_max)
#define png_get_pixel_aspect_ratio                      PNG_RENAME(png_get_pixel_aspect_ratio)
#define png_get_pixel_aspect_ratio_fixed                PNG_RENAME(png_get_pixel_aspect_ratio_fixed)
#define png_get_pixels_per_inch                         PNG_RENAME(png_get_pixels_per_inch)
#define png_get_pixels_per_meter                        PNG_RENAME(png_get_pixels_per_meter)
#define png_get_rgb_to_gray_status                      PNG_RENAME(png_get_rgb_to_gray_status)
#define png_get_rowbytes                                PNG_RENAME(png_get_rowbytes)
#define png_get_rows                                    PNG_RENAME(png_get_rows)
#define png_get_sBIT                                    PNG_RENAME(png_get_sBIT)
#define png_get_sCAL                                    PNG_RENAME(png_get_sCAL)
#define png_get_sCAL_fixed                              PNG_RENAME(png_get_sCAL_fixed)
#define png_get_sCAL_s                                  PNG_RENAME(png_get_sCAL_s)
#define png_get_sPLT                                    PNG_RENAME(png_get_sPLT)
#define png_get_sRGB                                    PNG_RENAME(png_get_sRGB)
#define png_get_signature                               PNG_RENAME(png_get_signature)
#define png_get_tIME                                    PNG_RENAME(png_get_tIME)
#define png_get_tRNS                                    PNG_RENAME(png_get_tRNS)
#define png_get_text                                    PNG_RENAME(png_get_text)
#define png_get_unknown_chunks                          PNG_RENAME(png_get_unknown_chunks)
#define png_get_user_chunk_ptr                          PNG_RENAME(png_get_user_chunk_ptr)
#define png_get_user_height_max                         PNG_RENAME(png_get_user_height_max)
#define png_get_user_width_max                          PNG_RENAME(png_get_user_width_max)
#define png_get_valid                                   PNG_RENAME(png_get_valid)
#define png_get_x_offset_inches                         PNG_RENAME(png_get_x_offset_inches)
#define png_get_x_offset_inches_fixed                   PNG_RENAME(png_get_x_offset_inches_fixed)
#define png_get_x_offset_microns                        PNG_RENAME(png_get_x_offset_microns)
#define png_get_x_offset_pixels                         PNG_RENAME(png_get_x_offset_pixels)
#define png_get_x_pixels_per_inch                       PNG_RENAME(png_get_x_pixels_per_inch)
#define png_get_x_pixels_per_meter                      PNG_RENAME(png_get_x_pixels_per_meter)
#define png_get_y_offset_inches                         PNG_RENAME(png_get_y_offset_inches)
#define png_get_y_offset_inches_fixed                   PNG_RENAME(png_get_y_offset_inches_fixed)
#define png_get_y_offset_microns                        PNG_RENAME(png_get_y_offset_microns)
#define png_get_y_offset_pixels                         PNG_RENAME(png_get_y_offset_pixels)
#define png_get_y_pixels_per_inch                       PNG_RENAME(png_get_y_pixels_per_inch)
#define png_get_y_pixels_per_meter                      PNG_RENAME(png_get_y_pixels_per_meter)
#define png_app_error                                   PNG_RENAME(png_app_error)
#define png_app_warning                                 PNG_RENAME(png_app_warning)
#define png_benign_error                                PNG_RENAME(png_benign_error)
#define png_chunk_benign_error                          PNG_RENAME(png_chunk_benign_error)
#define png_chunk_error                                 PNG_RENAME(png_chunk_error)
#define png_chunk_report                                PNG_RENAME(png_chunk_report)
#define png_chunk_warning                               PNG_RENAME(png_chunk_warning)
#define png_error                                       PNG_RENAME(png_error)
#define png_fixed_error                                 PNG_RENAME(png_fixed_error)
#define png_format_number                               PNG_RENAME(png_format_number)
#define png_formatted_warning                           PNG_RENAME(png_formatted_warning)
#define png_free_jmpbuf                                 PNG_RENAME(png_free_jmpbuf)
#define png_get_error_ptr                               PNG_RENAME(png_get_error_ptr)
#define png_longjmp                                     PNG_RENAME(png_longjmp)
#define png_safe_error                                  PNG_RENAME(png_safe_error)
#define png_safe_execute                                PNG_RENAME(png_safe_execute)
#define png_safe_warning                                PNG_RENAME(png_safe_warning)
#define png_safecat                                     PNG_RENAME(png_safecat)
#define png_set_error_fn                                PNG_RENAME(png_set_error_fn)
#define png_set_longjmp_fn                              PNG_RENAME(png_set_longjmp_fn)
#define png_warning                                     PNG_RENAME(png_warning)
#define png_warning_parameter                           PNG_RENAME(png_warning_parameter)
#define png_warning_parameter_signed                    PNG_RENAME(png_warning_parameter_signed)
#define png_warning_parameter_unsigned                  PNG_RENAME(png_warning_parameter_unsigned)
#define png_access_version_number                       PNG_RENAME(png_access_version_number)
#define png_ascii_from_fixed                            PNG_RENAME(png_ascii_from_fixed)
#define png_ascii_from_fp                               PNG_RENAME(png_ascii_from_fp)
#define png_build_gamma_table                           PNG_RENAME(png_build_gamma_table)
#define png_build_grayscale_palette                     PNG_RENAME(png_build_grayscale_palette)
#define png_calculate_crc                               PNG_RENAME(png_calculate_crc)
#define png_check_IHDR                                  PNG_RENAME(png_check_IHDR)
#define png_check_fp_number                             PNG_RENAME(png_check_fp_number)
#define png_check_fp_string                             PNG_RENAME(png_check_fp_string)
#define png_chunk_unknown_handling                      PNG_RENAME(png_chunk_unknown_handling)
#define png_colorspace_set_ICC                          PNG_RENAME(png_colorspace_set_ICC)
#define png_colorspace_set_chromaticities               PNG_RENAME(png_colorspace_set_chromaticities)
#define png_colorspace_set_endpoints                    PNG_RENAME(png_colorspace_set_endpoints)
#define png_colorspace_set_gamma                        PNG_RENAME(png_colorspace_set_gamma)
#define png_colorspace_set_rgb_coefficients             PNG_RENAME(png_colorspace_set_rgb_coefficients)
#define png_colorspace_set_sRGB                         PNG_RENAME(png_colorspace_set_sRGB)
#define png_colorspace_sync                             PNG_RENAME(png_colorspace_sync)
#define png_colorspace_sync_info                        PNG_RENAME(png_colorspace_sync_info)
#define png_convert_to_rfc1123                          PNG_RENAME(png_convert_to_rfc1123)
#define png_convert_to_rfc1123_buffer                   PNG_RENAME(png_convert_to_rfc1123_buffer)
#define png_create_info_struct                          PNG_RENAME(png_create_info_struct)
#define png_create_png_struct                           PNG_RENAME(png_create_png_struct)
#define png_data_freer                                  PNG_RENAME(png_data_freer)
#define png_destroy_gamma_table                         PNG_RENAME(png_destroy_gamma_table)
#define png_destroy_info_struct                         PNG_RENAME(png_destroy_info_struct)
#define png_fixed                                       PNG_RENAME(png_fixed)
#define png_free_data                                   PNG_RENAME(png_free_data)
#define png_gamma_16bit_correct                         PNG_RENAME(png_gamma_16bit_correct)
#define png_gamma_8bit_correct                          PNG_RENAME(png_gamma_8bit_correct)
#define png_gamma_correct                               PNG_RENAME(png_gamma_correct)
#define png_gamma_significant                           PNG_RENAME(png_gamma_significant)
#define png_get_copyright                               PNG_RENAME(png_get_copyright)
#define png_get_header_ver                              PNG_RENAME(png_get_header_ver)
#define png_get_header_version                          PNG_RENAME(png_get_header_version)
#define png_get_io_ptr                                  PNG_RENAME(png_get_io_ptr)
#define png_get_libpng_ver                              PNG_RENAME(png_get_libpng_ver)
#define png_handle_as_unknown                           PNG_RENAME(png_handle_as_unknown)
#define png_icc_check_header                            PNG_RENAME(png_icc_check_header)
#define png_icc_check_length                            PNG_RENAME(png_icc_check_length)
#define png_icc_check_tag_table                         PNG_RENAME(png_icc_check_tag_table)
#define png_icc_set_sRGB                                PNG_RENAME(png_icc_set_sRGB)
#define png_image_error                                 PNG_RENAME(png_image_error)
#define png_image_free                                  PNG_RENAME(png_image_free)
#define png_info_init_3                                 PNG_RENAME(png_info_init_3)
#define png_init_io                                     PNG_RENAME(png_init_io)
#define png_muldiv                                      PNG_RENAME(png_muldiv)
#define png_muldiv_warn                                 PNG_RENAME(png_muldiv_warn)
#define png_reciprocal                                  PNG_RENAME(png_reciprocal)
#define png_reciprocal2                                 PNG_RENAME(png_reciprocal2)
#define png_reset_crc                                   PNG_RENAME(png_reset_crc)
#define png_reset_zstream                               PNG_RENAME(png_reset_zstream)
#define png_sRGB_base                                   PNG_RENAME(png_sRGB_base)
#define png_sRGB_delta                                  PNG_RENAME(png_sRGB_delta)
#define png_sRGB_table                                  PNG_RENAME(png_sRGB_table)
#define png_save_int_32                                 PNG_RENAME(png_save_int_32)
#define png_set_option                                  PNG_RENAME(png_set_option)
#define png_set_sig_bytes                               PNG_RENAME(png_set_sig_bytes)
#define png_sig_cmp                                     PNG_RENAME(png_sig_cmp)
#define png_user_version_check                          PNG_RENAME(png_user_version_check)
#define png_zalloc                                      PNG_RENAME(png_zalloc)
#define png_zfree                                       PNG_RENAME(png_zfree)
#define png_zstream_error                               PNG_RENAME(png_zstream_error)

#endif // PNGRENAME_H