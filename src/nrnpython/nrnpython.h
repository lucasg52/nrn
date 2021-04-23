#ifndef nrnpython_h
#define nrnpython_h

#ifdef _WIN64
#define MS_WIN64
#define MS_WIN32
#define MS_WINDOWS
#endif

#include <../../nrnconf.h>
#include <nrnpython_config.h>

#if defined(NRNPYTHON_DYNAMICLOAD) && NRNPYTHON_DYNAMICLOAD >= 30
#define PY_LIMITED_API
#endif

#if defined(USE_PYTHON)
#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE
#if defined(__MINGW32__)
//at least a problem with g++6.3.0
#define _hypot hypot
#endif
#include <nrnwrap_Python.h>

#if (PY_MAJOR_VERSION >= 3)
#define myPyMODINIT_FUNC PyObject *
#else
#define myPyMODINIT_FUNC void

#ifndef PyMODINIT_FUNC /* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif /*PyMODINIT_FUNC*/
#ifndef PY_FORMAT_SIZE_T
#define Py_ssize_t int
#endif /*PY_FORMAT_SIZE_T*/
#endif /* PY_MAJOR_VERSION */

#endif /*USE_PYTHON*/

#if (PY_MAJOR_VERSION >= 3)
#define PyString_FromString PyUnicode_FromString
#define PyInt_Check PyLong_Check
#define PyInt_CheckExact PyLong_CheckExact
#define PyInt_AS_LONG PyLong_AsLong
#define PyInt_AsLong PyLong_AsLong
#define PyInt_FromLong PyLong_FromLong
#endif

#if defined(__cplusplus)
extern "C" {
#endif

extern PyObject* nrnpy_hoc_pop();
extern int nrnpy_numbercheck(PyObject*);

#if defined(__SIZEOF_POINTER__) && __SIZEOF_POINTER__ > __SIZEOF_LONG__
#define castptr2long (long)(long long)
#else
#define castptr2long (long)
#endif

#if defined(__cplusplus)
}
#endif


/*
Because python types have so many methods, attempt to do all set and get
using a PyHocObject which has different amounts filled in as the information
is gathered with a view toward ultimately making a call to hoc_object_component.
That requires that array indices or function arguments are on the stack.
The major variant is that we may be at the top level. The function arg
case is easy since they all come as a tuple in the call method. The
array indices come sequentially with a series of calls to the
sequence method. A nice side effect of intermediate objects is the extra
efficiency of reuse that avoids symbol lookup. Sadly, the scalar case does
not give this since the value is set/get instead of  returning the
intermediate.
*/
namespace PyHoc {
enum ObjectType {
  HocTopLevelInterpreter = 0,
  HocObject = 1,
  HocFunction = 2,  // function or TEMPLATE
  HocArray = 3,
  HocRefNum = 4,
  HocRefStr = 5,
  HocRefObj = 6,
  HocForallSectionIterator = 7,
  HocSectionListIterator = 8,
  HocScalarPtr = 9,
  HocArrayIncomplete =
      10,  // incomplete pointer to a hoc array (similar to HocArray)
  HocRefPStr = 11,
};
enum IteratorState {
  Begin,
  NextNotLast,
  Last
};
}  // namespace PyHoc

#endif

