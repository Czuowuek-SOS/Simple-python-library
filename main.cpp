#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <windows.h>
#include <conio.h>

#include "ansi.h"

/* Input&Output */

static PyObject* putString(PyObject* self, PyObject* args)
{
    const char* s;
    if(PyArg_ParseTuple(args, "s", &s))
    {
        std::cout << s;
        Py_RETURN_NONE;
    }
}

static PyObject* getChar(PyObject* self, PyObject* args)
{
    char c = getch();
    return PyLong_FromLong((int)c);
}

/* File I&O */

static PyObject* readContent(PyObject* self, PyObject* args)
{
    char* filename;
    if(PyArg_ParseTuple(args, "s", &filename))
    {
        FILE* fp = fopen(filename, "r");

        if(fp == NULL)
        {
            std::cout << red << "file not found\n" << reset;
            Py_RETURN_NONE;
        }

        char ch;        
        while(feof(fp))
        {
            ch = fgetc(fp);
            std::cout << ch;
            // putchar(ch);
        }

        putch('\n');

        fclose(fp);
        Py_RETURN_NONE;
    }
}

static PyObject* overwiteContent(PyObject* self, PyObject* args)
{
    char* filename;
    if(PyArg_ParseTuple(args, "s", &filename))
    {
        FILE* fp = fopen(filename, "w");

        if(fp == NULL)
        {
            std::cout << red << "file not found\n" << reset;
            Py_RETURN_NONE;
        }

        freopen(NULL,"w+",fp);
    }
}

/* Randoms */

/* Math */

static PyObject* add(PyObject* self, PyObject* args)
{
    int a, b;
    if(PyArg_ParseTuple(args, "ii", &a, &b))
    {
        return Py_BuildValue("i", a + b);
    }
}

/* Time */

static PyObject* getDate(PyObject* self, PyObject* args)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return Py_BuildValue("iiiiii", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

/* ... */
static PyMethodDef CLibMethods[] = 
{
    // I&O
    {"putString", putString, METH_VARARGS, "Characters output"},
    {"getChar", getChar, METH_NOARGS, "One character input as int"},
    // File IO
    {"readContent", readContent, METH_VARARGS, "Reads the file content"},
    {"overwriteContent", overwiteContent, METH_VARARGS, "Overwrite the file content"},
    // Randoms
    // 
    {"add", add, METH_VARARGS, "Add two ints"},
    // Time
    {"getDate", getDate, METH_VARARGS, "Get a date"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef CLibModule = 
{
    PyModuleDef_HEAD_INIT,
    "CLib",
    "Python Library",
    -1,
    CLibMethods
};

PyMODINIT_FUNC PyInit_CLib(void)
{
    srand(time(NULL));
    return PyModule_Create(&CLibModule);
}