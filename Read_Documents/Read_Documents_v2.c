#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 4096

bool isTextFile(const char *filename) {
    // Список разрешенных расширений
    const char *text_extensions[] = 
    {
        ".txt", 
        ".c", 
        ".cpp", 
        ".h", 
        ".py", 
        ".java", 
        ".html", 
        ".css", 
        ".js", 
        ".xml", 
        ".json", 
        ".odt",
        ".rtf "
        ".html", 
        ".htm",
        ".xml",
        ".csv",
        ".log",
        ".ini",
        ".json",
        ".md",
        ".tex",
        ".cfg",
        ".conf",
        ".properties",
        ".yml",
        ".yaml",
        NULL
    };

    // Получаем расширение файла
    char *extension = strrchr(filename, '.');

    if (extension == NULL) {
        return false; // Нет расширения - считаем не текстовым
    }

    // Сравниваем расширение с разрешенными
    for (int i = 0; text_extensions[i] != NULL; i++) {
        if (strcmp(extension, text_extensions[i]) == 0) {
            return true;
        }
    }

    return false; 
}

int main (int argc, char **argv) {
    
    char symbol;
    char symbol_v2;

    if (argc > 1) {
        printf("Переданный файл: %s\n", argv[1]);
    } else {
        printf("Файл не указан.\n");
        return 1;
    }

    if (isTextFile(argv[1])) {
        printf("Файл %s является текстовым.\n", argv[1]);
    } else {
        printf("Файл %s не является текстовым.\n", argv[1]);
    }

    FILE *inputFile = fopen(argv[1], "rb");
    if (inputFile == NULL) {
        printf("Не удалось открыть файл %s\n", argv[1]);
        return 1;
    }

    FILE *outputFile = fopen("Redaction_File", "wb");
    if (outputFile == NULL) {
        printf("Не удалось создать файл %s для записи\n", argv[1]);
        fclose(inputFile);
        return 1;
    };

    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, inputFile)) > 0) {
        for (size_t j = 0; j < bytesRead; j++) {
            if (buffer[j] == symbol) {
                buffer[j] = symbol_v2;
            }
        }

        fwrite(buffer, 1, bytesRead, outputFile);
        printf("Прочитано %zu байт: %.*s\n", bytesRead, (int)bytesRead, buffer);
    }
    
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}