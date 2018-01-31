#include <Python.h>
#include "pynetinit.h"

static PyObject *sum_simple(PyObject *self, PyObject *args);
static char sum_docstring[] = "Calculate the sum of two doubles.";

/* List of functions defined in the module */
static PyMethodDef clr_methods[] = {
    {"sum", sum_simple, METH_VARARGS, sum_docstring},
    {NULL, NULL, 0, NULL}
};

PyDoc_STRVAR(clr_module_doc,
             "clr facade module to initialize the CLR. It's later "
             "replaced by the real clr module. This module has a facade "
             "attribute to make it distinguishable from the real clr module."
);

static PyNet_Args *pn_args;
char **environ = NULL;

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef clrdef = {
    PyModuleDef_HEAD_INIT,
    "clr",               /* m_name */
    clr_module_doc,      /* m_doc */
    -1,                  /* m_size */
    clr_methods,         /* m_methods */
    NULL,                /* m_reload */
    NULL,                /* m_traverse */
    NULL,                /* m_clear */
    NULL,                /* m_free */
};
#endif

static PyObject *sum_simple(PyObject *self, PyObject *args)
{
    double a, b;

    /* Parse the input tuple */
    if (!PyArg_ParseTuple(args, "dd", &a, &b))
        return NULL;

    /* Call the external C++ function to compute the sum. */
    double value = sum(pn_args, a, b);

    if (pn_args->error != NULL)
    {
        PyErr_SetString(PyExc_ImportError, pn_args->error);
        return NULL;
    }

    /* Build the output tuple */
    PyObject *ret = Py_BuildValue("d", value);
    return ret;
}

static PyObject *_initclr()
{
    PyObject *m;

    /* Create the module and add the functions */
#if PY_MAJOR_VERSION >= 3
    m = PyModule_Create(&clrdef);
#else
    m = Py_InitModule3("clr", clr_methods, clr_module_doc);
#endif
    if (m == NULL)
        return NULL;

    PyModule_AddObject(m, "facade", Py_True);
    Py_INCREF(Py_True);

    pn_args = PyNet_Init(1);

    if (pn_args->error != NULL)
    {
        PyErr_SetString(PyExc_ImportError, pn_args->error);
        return NULL;
    }

    return m;
}

#if PY_MAJOR_VERSION >= 3
PyMODINIT_FUNC
PyInit_clr(void)
{
    return _initclr();
}
#else
PyMODINIT_FUNC
initclr(void)
{
    _initclr();
}
#endif
