#ifndef DATASAVE
#define DATASAVE

#include <stdio.h>
#include <string.h>

class Data
{
    private:
        char path[100];

        int WordPositionInFile(FILE *file, const char word[]);
        int GetFileSize(FILE *file);
        void SaveLogic(FILE *file, const char key[], bool isArr = false, int sizeArr = 0);

    public:
        Data(const char _path[] = "dataSave.dat")
        {
            strcpy(path, _path);
        }

        template <typename type>
        void Save(const char key[], type value);

        template <typename type>
        void Save(const char key[], const type arrValues[], int arrSize);

        template <typename type>
        void Load(const char key[], type *value);

        template <typename type>
        void Load(const char key[], type arrValues[], int arrSize);
};

//Сохранение переменных
template <typename type>
void Data::Save(const char key[], type value)
{
    FILE *file = fopen(path, "ab");
    fclose(file);

    file = fopen(path, "r+b");

    SaveLogic(file, key);

    fwrite(&value, sizeof(type), 1, file);

    fclose(file);
}

//Сохранение массива
template <typename type>
void Data::Save(const char key[], const type arrValues[], int arrSize)
{
    FILE *file = fopen(path, "ab");
    fclose(file);

    file = fopen(path, "r+b");

    SaveLogic(file, key, true, arrSize);

    fwrite(arrValues, sizeof(type), arrSize, file);

    fclose(file);
}

//Логика сохранения(перемещеает курсор в позицию после ключа)
void Data::SaveLogic(FILE *file, const char key[], bool isArr, int sizeArr)
{
    int wordPos = WordPositionInFile(file, key);

    if(wordPos == -1)
    {
        if(GetFileSize(file) > 0) fputc('\n', file);

        fseek(file, 0, SEEK_END);

        fprintf(file, "%s", key);

        if(isArr)
        {
            fwrite(&sizeArr, sizeof(int), 1, file);
        }
    }
    else
    {
        int pos = 1;

        if(isArr) pos = 5;

        fseek(file, wordPos + pos, SEEK_SET);
    }
}

//Загрузка переменной
template <typename type>
void Data::Load(const char key[], type *value)
{
    FILE *file = fopen(path, "rb");

    if(file == NULL) return;

    int wordPos = WordPositionInFile(file, key);

    if(wordPos == -1) return;

    fseek(file, wordPos + 1, SEEK_SET);

    fread(value, sizeof(type), 1, file);

    fclose(file);
}

//Загрузка массива
template <typename type>
void Data::Load(const char key[], type arrValues[], int arrSize)
{
    FILE *file = fopen(path, "rb");

    if(file == NULL) return;

    int wordPos = WordPositionInFile(file, key);

    if(wordPos == -1) return;

    fseek(file, wordPos + 1, SEEK_SET);

    int arrSizeMax = 0;
    fread(&arrSizeMax, sizeof(int), 1, file);

    if(arrSize > arrSizeMax) arrSize = arrSizeMax;

    fread(arrValues, sizeof(type), arrSize, file);

    fclose(file);
}

//Возращает позицию последней буквы в файле
int Data::WordPositionInFile(FILE *file, const char word[])
{
    fseek(file, 0, SEEK_SET);

    int positionWord = -1;

    int nowPositionWord = 0;
    int positionInFile = 0;
    while(true)
    {
        int ch = getc(file);

        if(ch == EOF) break;

        if(word[nowPositionWord] == ch)
        {
            nowPositionWord++;
        }
        else
        {
            nowPositionWord = 0;
        }

        if(nowPositionWord == strlen(word))
        {
            positionWord = positionInFile;
            break;
        }

        positionInFile++;
    }

    return positionWord;
}

//Количество символов в файле
int Data::GetFileSize(FILE *file)
{
    int fileSize = 0;
    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);

    return fileSize;
}

#endif