#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <shlwapi.h>
#include <stdbool.h>
#include <winbase.h>

#define BUFFER_SIZE 4096

#ifndef CSIDL_PERSONAL
#define CSIDL_PERSONAL 0x0005
#endif

#include <shlobj.h>

bool isTextFile(const char *filename) {
    // Список разрешенных расширений
    const char *text_extensions[] = {
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
    }; // NULL

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
   
  
    if (argc > 1) {
      printf("Переданный файл: %s\n", argv[1]);

      if (isTextFile(argv[1])) 
      {
         printf("Файл %s является текстовым.\n", argv[1]);
        
         FILE *inputFile;
         FILE *outputFile;
         char buffer[BUFFER_SIZE];
         char fileName[MAX_PATH];
         char exeDir[MAX_PATH];
         int partNumber = 1;
         size_t bytesRead;

            // Получаем путь к директории с исполняемым файлом
         GetModuleFileName(NULL, exeDir, MAX_PATH);
         PathRemoveFileSpec(exeDir);

           
         inputFile = fopen(argv[1], "rb");
         if (inputFile == NULL) 
         {
            printf("Не удалось открыть входной файл.\n");
            perror("Ошибка открытия файла");
            return 1;
         }
            
         while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, inputFile)) > 0) 
         {
            snprintf(fileName, sizeof(fileName), "%s/part_%d.txt", exeDir, partNumber);
            outputFile = fopen(fileName, "wb");
            if (outputFile == NULL) 
            {
            printf("Не удалось создать выходной файл %s.\n", fileName);
            fclose(inputFile);
            return 1;
            }
         }

         fwrite(buffer, 1, bytesRead, outputFile);
         fclose(outputFile);
         partNumber++;

         for (int i = 1; i < partNumber; i++) 
         {
         snprintf(fileName, sizeof(fileName), "%s/part_%d.txt", exeDir, i);
         FILE *file = fopen(fileName, "rb+");
         if (file == NULL) 
         {
            printf("Не удалось открыть файл %s для изменения.\n", fileName);
            continue;
         }

         // Читаем содержимое файла
         char fileContent[BUFFER_SIZE];
         
         fseek(file, 0, SEEK_SET);

         size_t bytesRead = fread(fileContent, 1, BUFFER_SIZE, file);
         
         for (size_t j = 0; j < bytesRead; j++) 
         {
            if (fileContent[j] == ' ') 
            {
                fileContent[j] = '_';
            }
         }
         
         
         // Перемещаем указатель файла в начало
         
         fseek(file, 0, SEEK_SET);
         // Записываем измененное содержимое обратно в файл
         fwrite(fileContent, 1, bytesRead, file);
         
         fclose(file);
         }
      

      } 
      
      else 
         {
            printf("Файл %s не является текстовым.\n", argv[1]);
         }
   }

   else 


   {
      printf("Файл не указан.\n");
      return 1;
   }


   return 0;
}
