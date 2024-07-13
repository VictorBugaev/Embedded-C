#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jpeglib.h>

int main() {
    struct jpeg_decompress_struct cinfo1, cinfo2;
    struct jpeg_compress_struct cinfo_out;
    struct jpeg_error_mgr jerr1, jerr2, jerr_out;

    for(int i = 1; i < 487; i++){
        FILE *fd1 = fopen("panorama.jpeg", "rb");
        if (fd1 == NULL) {
            perror("File 1 open error");
            return -1;
        }

        char tmp[10];
        char jpeg[] = ".jpeg";
        sprintf(tmp, "%d%s", i, jpeg);
        printf("%s\n", tmp);
        
        FILE *fd2 = fopen(tmp, "rb");
        if (fd2 == NULL) {
            perror("File 2 open error");
            fclose(fd1);
            return -1;
        }
        FILE *fd_out = fopen("result.jpeg", "wb");
        if (fd_out == NULL) {
            perror("File result open/create error");
            fclose(fd1);
            fclose(fd2);
            return -1;
        }

        cinfo1.err = jpeg_std_error(&jerr1);
        jpeg_create_decompress(&cinfo1);
        cinfo2.err = jpeg_std_error(&jerr2);
        jpeg_create_decompress(&cinfo2);

        jpeg_stdio_src(&cinfo1, fd1);
        jpeg_stdio_src(&cinfo2, fd2);

        jpeg_read_header(&cinfo1, TRUE);
        jpeg_read_header(&cinfo2, TRUE);

        jpeg_start_decompress(&cinfo1);
        jpeg_start_decompress(&cinfo2);

        if (cinfo1.output_height != cinfo2.output_height || cinfo1.output_components != cinfo2.output_components) {
            fprintf(stderr, "Images have different heights or color components\n");
            jpeg_destroy_decompress(&cinfo1);
            jpeg_destroy_decompress(&cinfo2);
            fclose(fd1);
            fclose(fd2);
            fclose(fd_out);
            return -1;
        }

        JDIMENSION image_width = cinfo1.output_width+18;//cinfo1.output_width+18;
        JDIMENSION image_height = cinfo1.output_height;

        cinfo_out.err = jpeg_std_error(&jerr_out);
        jpeg_create_compress(&cinfo_out);
        jpeg_stdio_dest(&cinfo_out, fd_out);

        cinfo_out.image_width = image_width;
        cinfo_out.image_height = image_height;
        cinfo_out.input_components = cinfo1.output_components;
        cinfo_out.in_color_space = cinfo1.out_color_space;

        jpeg_set_defaults(&cinfo_out);
        jpeg_start_compress(&cinfo_out, TRUE);

        JSAMPARRAY buffer1 = (*cinfo1.mem->alloc_sarray)((j_common_ptr)&cinfo1, JPOOL_IMAGE, cinfo1.output_width * cinfo1.output_components, 1);
        JSAMPARRAY buffer2 = (*cinfo2.mem->alloc_sarray)((j_common_ptr)&cinfo2, JPOOL_IMAGE, cinfo2.output_width * cinfo2.output_components, 1);
        JSAMPARRAY out_buffer = (*cinfo_out.mem->alloc_sarray)((j_common_ptr)&cinfo_out, JPOOL_IMAGE, image_width * cinfo_out.input_components, 1);
        
        while (cinfo1.output_scanline < cinfo1.output_height) {
            jpeg_read_scanlines(&cinfo1, buffer1, 1);
            jpeg_read_scanlines(&cinfo2, buffer2, 1);

            memcpy(out_buffer[0], buffer1[0], (cinfo1.output_width/2) * cinfo1.output_components);
            memcpy(out_buffer[0] + (cinfo1.output_width/2 ) * cinfo1.output_components, buffer2[0] + (cinfo2.output_width/2 + 10)* cinfo2.output_components, (cinfo2.output_width/2) * cinfo2.output_components);
            jpeg_write_scanlines(&cinfo_out, out_buffer, 1);

        }

        jpeg_finish_decompress(&cinfo1);
        jpeg_destroy_decompress(&cinfo1);

        jpeg_finish_decompress(&cinfo2);
        jpeg_destroy_decompress(&cinfo2);

        jpeg_finish_compress(&cinfo_out);
        jpeg_destroy_compress(&cinfo_out);

        fclose(fd1);
        fclose(fd2);
        fclose(fd_out);

        if (remove("panorama.jpeg") != 0) {
            perror("Error removing original panorama.jpeg");
            return -1;
        }
        if (rename("result.jpeg", "panorama.jpeg") != 0) {
            perror("Error renaming result.jpeg to panorama.jpeg");
            return -1;
        }
        if (remove(tmp) != 0) {
            perror("Error removing tmp.jpeg");
            return -1;
        }
    }
    return 0;
}
