/*-----------------------------------------------------------------------------
| Copyright (c) 2014, Nucleic Development Team.
|
| Distributed under the terms of the Modified BSD License.
|
| The full license is in the file COPYING.txt, distributed with this software.
|----------------------------------------------------------------------------*/
#pragma once

#include "stdint.h"

#include <Python.h>


namespace atom
{

extern PyObject* ValidationError;


// POD struct - all member fields are considered private
struct Member
{
	PyObject_HEAD
	PyObject* m_metadata;
	PyObject* m_default_context;
	PyObject* m_validate_context;
	PyObject* m_post_validate_context;
	PyObject* m_post_setattr_context;
	uint8_t m_default_mode;
	uint8_t m_validate_mode;
	uint8_t m_post_validate_mode;
	uint8_t m_post_setattr_mode;

	enum DefaultMode
	{
		NoDefault,
		DefaultValue,
		DefaultFactory,
		DefaultCallObject,
		DefaultAtomMethod,
		DefaultMemberMethod,
		DefaultLast // sentinel
	};

	enum ValidateMode
	{
		NoValidate,
		ValidateBool,
		ValidateInt,
		ValidateFloat,
		ValidateBytes,
		ValidateStr,
		ValidateUnicode,
		ValidateTyped,
		ValidateInstance,
		ValidateSubclass,
		ValidateEnum,
		ValidateCallable,
		ValidateRange,
		ValidateCoerced,
		ValidateCallObject,
		ValidateAtomMethod,
		ValidateMemberMethod,
		ValidateLast // sentinel
	};

	enum PostValidateMode
	{
		NoPostValidate,
		PostValidateCallObject,
		PostValidateAtomMethod,
		PostValidateMemberMethod,
		PostValidateLast // sentinel
	};

	enum PostSetAttrMode
	{
		NoPostSetAttr,
		PostSetAttrCallObject,
		PostSetAttrAtomMethod,
		PostSetAttrMemberMethod,
		PostSetAttrLast // sentinel
	};

	static PyTypeObject TypeObject;

	static bool Ready();

	static bool TypeCheck( PyObject* ob )
	{
		return PyObject_TypeCheck( ob, &TypeObject ) != 0;
	}

	PyObject* defaultValue( PyObject* atom, PyObject* name );

	PyObject* validateValue( PyObject* atom, PyObject* name, PyObject* value );

	int postSetAttrValue( PyObject* atom, PyObject* name, PyObject* value );
};

} // namespace atom
