#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <windows.h>
#include <conio.h>

#include "ansi.h"


/* Custom types */

typedef struct 
{
    PyObject_HEAD
    char ch;
} PyCharObject;

/*
static PyObject* PyChar_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PyCharObject* self;
    self = (PyCharObject*) type->tp_alloc(type, 0);
    if (self != NULL) {
        self->ch = PyUnicode_FromString("");
        if (self->ch == NULL) {
            Py_DECREF(self);
            return NULL;
        }
    Py_RETURN_NONE;
}
*/

static int PyChar_init(PyCharObject* self, PyObject* args)
{
    return 0;
}

static void PyChar_dealloc(PyCharObject* self)
{
    Py_XDECREF(self->ch);
    Py_TYPE(self)->tp_free((PyObject *) self);
}

static PyObject* PyChar_string(PyTypeObject* type ,PyObject* self, PyObject* args)
{
    Py_RETURN_NONE;
}


static PyMemberDef PyChar_members[] =
{
    {"string", T_OBJECT_EX, offsetof(PyCharObject, ch), 0, {"Convert PyCharObject to string"},

    {NULL}  /* Sentinel */
};

static PyTypeObject CharType =
{
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "CLib.char",
    .tp_itemsize = 0,
    .tp_doc = PyDoc_STR("Char type for python"),
    .tp_init = (initproc)PyChar_init,
    .tp_new = PyType_GenericNew,
    .tp_dealloc = (destructor)PyChar_dealloc,

    .tp_members = PyChar_members,
};




/* - - - - - -  */

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

/* other */

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
    PyObject* module = PyModule_Create(&CLibModule);

    srand(time(NULL));


    PyModule_AddStringConstant(module, "red", red);
    PyModule_AddStringConstant(module, "green", green);
    PyModule_AddStringConstant(module, "yellow", yellow);
    PyModule_AddStringConstant(module, "blue", blue);
    PyModule_AddStringConstant(module, "magenta", magenta);
    PyModule_AddStringConstant(module, "cyan", cyan);
    PyModule_AddStringConstant(module, "white", white);
    PyModule_AddStringConstant(module, "fiolet", fiolet);
    PyModule_AddStringConstant(module, "reset", reset);


    if (PyType_Ready(&CharType) < 0)
    {
        return NULL;
    }

    Py_INCREF(&CharType);
    if (PyModule_AddObject(module, "char", (PyObject *) &CharType) < 0)
    {
        Py_DECREF(&CharType);
        Py_DECREF(module);
        return NULL;
    }

    return module;
}
