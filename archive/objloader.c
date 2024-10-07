#include "objloader.h"

void load_obj(const char* file_path, mesh* out){
    FILE *fptr = fopen(file_path, "r");
    if(fptr == NULL) {
        printf("Not able to open %s. Cannot load obj.", file_path);
        return;
    }
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    out->face_count = 0;
    out->vertex_count = 0;
    while ((read = getline(&line, &len, fptr)) != -1) {
        if (line[0] == 'v'){
            char buffer[20] = "";
            size_t curr_char_idx = 0;
            int cnt = 0;
            for (int i = 2; i < len; i++){
                if (isspace(line[i]) && cnt < 3){
                    if (cnt == 0){
                        out->vertices[out->vertex_count].x = atof(buffer);
                    }else if (cnt == 1){
                        out->vertices[out->vertex_count].y = atof(buffer);
                    }else if (cnt == 2){
                        out->vertices[out->vertex_count].z = atof(buffer);
                    }
                    cnt++;
                    strcpy(buffer, "");
                    curr_char_idx = 0;
                }else{
                    buffer[curr_char_idx] = line[i];
                    buffer[curr_char_idx+1] = '\0';
                    curr_char_idx++;
                }
            }
            out->vertex_count++;
        }else if (line[0] == 'f'){
            char buffer[20] = "";
            size_t curr_char_idx = 0;
            int cnt = 0;
            for (int i = 2; i < len; i++){
                if (isspace(line[i]) && cnt < 3){
                    out->faces[out->face_count].vertex_indices[cnt] = atoi(buffer) - 1;
                    cnt++;
                    strcpy(buffer, "");
                    curr_char_idx = 0;
                }else{
                    buffer[curr_char_idx] = line[i];
                    buffer[curr_char_idx+1] = '\0';
                    curr_char_idx++;
                }
            }
            out->face_count++;
        }
    }

    fclose(fptr); 
}