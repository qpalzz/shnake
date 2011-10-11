#ifndef FREETYPE_H_INCLUDED
#define FREETYPE_H_INCLUDED

// FreeType заголовочные файлы
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

// OpenGL заголовочные файлы
#include <GL/gl.h>
#include <GL/glu.h>

// Некоторые заголовки STL
#include <vector>
#include <string>

// Использование STL библиотеки исключений увеличивает шансы
// на то, что другой человек будет корректно отлавливать посылаемые нами исключения.
#include <stdexcept>

//Помещая все в пространство имен, мы можем, не беспокоится о конфликте с чужим
// кодом такой распространенной функцией как print
namespace freetype {

    // В этом пространстве, даем себе возможность написать только "vector" вместо "std::vector"
    using std::vector;

    // тоже самое для строки.
    using std::string;

    // Здесь мы храним всю информацию о FreeType шрифте, который мы хотим создать
    struct font_data {
        float h;                    // Высота
        GLuint * textures;          // Идентификатор
        GLuint list_base;           // Содержит указатель на список отображения

        // Функция инициализации создаст шрифт с
        // высотой h из файла fname
        void init(const char * fname, unsigned int h);

        // Освобождаем ресурсы связанные со шрифтом
        void clean();
    };

    // Главная функция библиотеки -  она будет печатать
    // текст в окне по координатам X,Y используя Font ft_font.
    // Текущая матрица вида модели также будет применена к тексту

    void print(const font_data &ft_font, float x, float y, const char *fmt, ...);

}                        // Закрываем пространство имен

#endif // FREETYPE_H_INCLUDED
