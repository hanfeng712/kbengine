/*
This source file is part of KBEngine
For the latest info, see http://www.kbengine.org/

Copyright (c) 2008-2012 KBEngine.

KBEngine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

KBEngine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.
 
You should have received a copy of the GNU Lesser General Public License
along with KBEngine.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "datatype.hpp"
#include "datatypes.hpp"
#include "fixeddict.hpp"
#include "fixedarray.hpp"
#include "pyscript/vector2.hpp"
#include "pyscript/vector3.hpp"
#include "pyscript/vector4.hpp"
	
namespace KBEngine{
static DATATYPE_UID _g_dataTypeUID = 1;

//-------------------------------------------------------------------------------------
DataType::DataType(DATATYPE_UID did):
id_(did),
aliasName_()
{
	if(id_ == 0)
		id_ = _g_dataTypeUID++;

	DataTypes::addDateType(id_, this);
}

//-------------------------------------------------------------------------------------
DataType::~DataType()
{
}

//-------------------------------------------------------------------------------------
bool DataType::initialize(XmlPlus* xmlplus, TiXmlNode* node)
{
	return true;
}

//-------------------------------------------------------------------------------------
UInt64Type::UInt64Type(DATATYPE_UID did):
DataType(did)
{
}

//-------------------------------------------------------------------------------------
UInt64Type::~UInt64Type()
{
}

//-------------------------------------------------------------------------------------
bool UInt64Type::isSameType(PyObject* pyValue)
{
	if(pyValue == NULL)
	{
		OUT_TYPE_ERROR("UINT64");
		return false;
	}

	if (!PyLong_Check(pyValue))
		return false;

	PyLong_AsUnsignedLongLong(pyValue);
	if (!PyErr_Occurred()) 
		return true;
	
	PyErr_Clear();
	PyLong_AsUnsignedLong(pyValue);
	if (!PyErr_Occurred()) 
		return true;
	
	PyErr_Clear();
	long v = PyLong_AsLong(pyValue);
	if (!PyErr_Occurred()) 
	{
		if(v < 0)
		{
			OUT_TYPE_ERROR("UINT64");
			return false;
		}
		return true;
	}

	PyErr_Clear();
	OUT_TYPE_ERROR("UINT64");
	return false;
}

//-------------------------------------------------------------------------------------
PyObject* UInt64Type::parseDefaultStr(std::string defaultVal)
{
	uint64 val = 0;
	if(!defaultVal.empty())
	{
		std::stringstream stream;
		stream << defaultVal;
		stream >> val;
	}

	return PyLong_FromUnsignedLongLong(val);
}

//-------------------------------------------------------------------------------------
void UInt64Type::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
	uint64 udata = static_cast<uint64>(PyLong_AsUnsignedLongLong(pyValue));
	(*mstream) << udata;
}

//-------------------------------------------------------------------------------------
PyObject* UInt64Type::createFromStream(MemoryStream* mstream)
{
	uint64 val = 0;
	if(mstream)
		(*mstream) >> val;	
	return PyLong_FromUnsignedLongLong(val);
}

//-------------------------------------------------------------------------------------
UInt32Type::UInt32Type(DATATYPE_UID did):
DataType(did)
{
}

//-------------------------------------------------------------------------------------
UInt32Type::~UInt32Type()
{
}

//-------------------------------------------------------------------------------------
bool UInt32Type::isSameType(PyObject* pyValue)
{
	if(pyValue == NULL)
	{
		OUT_TYPE_ERROR("UINT32");
		return false;
	}

	if (!PyLong_Check(pyValue))
		return false;

	PyLong_AsUnsignedLong(pyValue);
	if (!PyErr_Occurred()) 
		return true;
	
	PyErr_Clear();
	long v = PyLong_AsLong(pyValue);
	if (!PyErr_Occurred()) 
	{
		if(v < 0)
		{
			OUT_TYPE_ERROR("UINT32");
			return false;
		}
		return true;
	}
	
	PyErr_Clear();
	OUT_TYPE_ERROR("UINT32");
	return false;
}

//-------------------------------------------------------------------------------------
PyObject* UInt32Type::parseDefaultStr(std::string defaultVal)
{
	uint32 val = 0;
	if(!defaultVal.empty())
	{
		std::stringstream stream;
		stream << defaultVal;
		stream >> val;
	}

	return PyLong_FromUnsignedLong(val);
}

//-------------------------------------------------------------------------------------
void UInt32Type::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
	uint32 v = PyLong_AsUnsignedLong(pyValue);
	(*mstream) << v;
}

//-------------------------------------------------------------------------------------
PyObject* UInt32Type::createFromStream(MemoryStream* mstream)
{
	uint32 val = 0;
	if(mstream)
		(*mstream) >> val;	
	return PyLong_FromUnsignedLong(val);
}

//-------------------------------------------------------------------------------------
Int64Type::Int64Type(DATATYPE_UID did):
DataType(did)
{
}

//-------------------------------------------------------------------------------------
Int64Type::~Int64Type()
{
}

//-------------------------------------------------------------------------------------
bool Int64Type::isSameType(PyObject* pyValue)
{
	if(pyValue == NULL)
	{
		OUT_TYPE_ERROR("INT64");
		return false;
	}

	if(!PyLong_Check(pyValue))
		return false;

	PyLong_AsLongLong(pyValue);
	if (!PyErr_Occurred()) 
		return true;

	PyErr_Clear();
	PyLong_AsLong(pyValue);
	if (!PyErr_Occurred()) 
	{
		return true;
	}

	PyErr_Clear();
	OUT_TYPE_ERROR("INT64");
	return false;
}

//-------------------------------------------------------------------------------------
PyObject* Int64Type::parseDefaultStr(std::string defaultVal)
{
	int64 val = 0;
	if(!defaultVal.empty())
	{
		std::stringstream stream;
		stream << defaultVal;
		stream >> val;
	}

	return PyLong_FromLongLong(val);
}

//-------------------------------------------------------------------------------------
void Int64Type::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
	int64 v = PyLong_AsLongLong(pyValue);
	(*mstream) << v;
}

//-------------------------------------------------------------------------------------
PyObject* Int64Type::createFromStream(MemoryStream* mstream)
{
	int64 val = 0;
	if(mstream)
		(*mstream) >> val;	
	return PyLong_FromLongLong(val);
}

//-------------------------------------------------------------------------------------
FloatType::FloatType(DATATYPE_UID did):
DataType(did)
{
}

//-------------------------------------------------------------------------------------
FloatType::~FloatType()
{
}

//-------------------------------------------------------------------------------------
bool FloatType::isSameType(PyObject* pyValue)
{
	if(pyValue == NULL)
	{
		OUT_TYPE_ERROR("FLOAT");
		return false;
	}

	bool ret = PyFloat_Check(pyValue);
	if(!ret)
		OUT_TYPE_ERROR("FLOAT");
	return ret;
}

//-------------------------------------------------------------------------------------
PyObject* FloatType::parseDefaultStr(std::string defaultVal)
{
	float val = 0.0f;
	if(!defaultVal.empty())
	{
		std::stringstream stream;
		stream << defaultVal;
		stream >> val;
	}

	return PyFloat_FromDouble(val);
}

//-------------------------------------------------------------------------------------
void FloatType::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
	float val = (float)PyFloat_AsDouble(pyValue);
	(*mstream) << val;
}

//-------------------------------------------------------------------------------------
PyObject* FloatType::createFromStream(MemoryStream* mstream)
{
	float val = 0.0;
	if(mstream)
		(*mstream) >> val;	
	return PyFloat_FromDouble(val);
}

//-------------------------------------------------------------------------------------
DoubleType::DoubleType(DATATYPE_UID did):
DataType(did)
{
}

//-------------------------------------------------------------------------------------
DoubleType::~DoubleType()
{
}

//-------------------------------------------------------------------------------------
bool DoubleType::isSameType(PyObject* pyValue)
{
	if(pyValue == NULL)
	{
		OUT_TYPE_ERROR("DOUBLE");
		return false;
	}

	bool ret = PyFloat_Check(pyValue);
	if(!ret)
		OUT_TYPE_ERROR("DOUBLE");
	return ret;
}

//-------------------------------------------------------------------------------------
PyObject* DoubleType::parseDefaultStr(std::string defaultVal)
{
	double val = 0.0f;
	if(!defaultVal.empty())
	{
		std::stringstream stream;
		stream << defaultVal;
		stream >> val;
	}

	return PyFloat_FromDouble(val);
}

//-------------------------------------------------------------------------------------
void DoubleType::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
	(*mstream) << PyFloat_AsDouble(pyValue);
}

//-------------------------------------------------------------------------------------
PyObject* DoubleType::createFromStream(MemoryStream* mstream)
{
	double val = 0.0;
	if(mstream)
		(*mstream) >> val;	
	return PyFloat_FromDouble(val);
}

//-------------------------------------------------------------------------------------
VectorType::VectorType(uint32 elemCount, DATATYPE_UID did):
DataType(did),
name_(),
elemCount_(elemCount)
{
	char tbuf[MAX_BUF];
	kbe_snprintf(tbuf, MAX_BUF, "VECTOR%u", elemCount);
	name_ += tbuf;
}

//-------------------------------------------------------------------------------------
VectorType::~VectorType()
{
}

//-------------------------------------------------------------------------------------
bool VectorType::isSameType(PyObject* pyValue)
{
	if(pyValue == NULL)
	{
		PyErr_Format(PyExc_TypeError, 
			"must be set to a VECTOR%d type.", elemCount_);
		
		PyErr_PrintEx(0);
		return false;
	}

	if(!PySequence_Check(pyValue) || PySequence_Size(pyValue) != elemCount_)
	{
		PyErr_Format(PyExc_TypeError, 
			"must be set to a VECTOR%d type.", elemCount_);
		
		PyErr_PrintEx(0);
		return false;
	}

	for(uint32 index=0; index<elemCount_; index++)
	{
		PyObject* pyVal = PySequence_GetItem(pyValue, index);
		if(!PyFloat_Check(pyVal) && !PyLong_Check(pyVal) && !PyLong_AsLongLong(pyVal))
		{
			PyErr_Format(PyExc_TypeError, 
				"VECTOR%d item is not digit.", elemCount_);
			
			PyErr_PrintEx(0);
			return false;
		}

		Py_DECREF(pyVal);
	}

	return true;
}

//-------------------------------------------------------------------------------------
PyObject* VectorType::parseDefaultStr(std::string defaultVal)
{
	float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;

	if(!defaultVal.empty())
	{
		std::stringstream stream;
		stream << defaultVal;

		switch(elemCount_)
		{
			case 2:
				stream >> x >> y;
				break;
			case 3:
				stream >> x >> y >> z;
				break;
			case 4:
				stream >> x >> y >> z >> w;
				break;
			default:
				break;
		}
	}

	switch(elemCount_)
	{
		case 2:
			return new script::ScriptVector2(float(x), float(y));
		case 3:
			return new script::ScriptVector3(float(x), float(y), float(z));
		case 4:
			return new script::ScriptVector4(float(x), float(y), float(z), float(w));
		default:
			break;
	}

	Py_RETURN_NONE;
}

//-------------------------------------------------------------------------------------
void VectorType::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
	(*mstream) << elemCount_;
	for(uint32 index=0; index<elemCount_; index++)
	{
		PyObject* pyVal = PySequence_GetItem(pyValue, index);
#ifdef CLIENT_NO_FLOAT
		int32 v = (int32)PyFloat_AsDouble(pyVal);
#else
		float v = (float)PyFloat_AsDouble(pyVal);
#endif
		(*mstream) << v;
		Py_DECREF(pyVal);
	}
}

//-------------------------------------------------------------------------------------
PyObject* VectorType::createFromStream(MemoryStream* mstream)
{
#ifdef CLIENT_NO_FLOAT
		int32 x = 0, y = 0, z = 0, w = 0;
#else
		float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;
#endif

	uint32 count = 0;
	(*mstream) >> count;
	
	if(count != elemCount_)
		return NULL;

	switch(elemCount_)
	{
		case 2:
			if(mstream)
				(*mstream) >> x >> y;	
			return new script::ScriptVector2(float(x), float(y));
		case 3:
			if(mstream)
				(*mstream) >> x >> y >> z;	
			return new script::ScriptVector3(float(x), float(y), float(z));
		case 4:
			if(mstream)
				(*mstream) >> x >> y >> z >> w;	
			return new script::ScriptVector4(float(x), float(y), float(z), float(w));
		default:
			break;
	}
	
	return NULL;
}

//-------------------------------------------------------------------------------------
StringType::StringType(DATATYPE_UID did):
DataType(did)
{
}

//-------------------------------------------------------------------------------------
StringType::~StringType()
{
}

//-------------------------------------------------------------------------------------
bool StringType::isSameType(PyObject* pyValue)
{
	if(pyValue == NULL)
	{
		OUT_TYPE_ERROR("STRING");
		return false;
	}

	bool ret = PyUnicode_Check(pyValue);
	if(!ret)
		OUT_TYPE_ERROR("STRING");
	return ret;
}

//-------------------------------------------------------------------------------------
PyObject* StringType::parseDefaultStr(std::string defaultVal)
{
	PyObject* pyobj = PyUnicode_FromString(defaultVal.c_str());

	if (pyobj && !PyErr_Occurred()) 
		return pyobj;

	PyErr_Clear();
	return PyUnicode_FromString("");
}

//-------------------------------------------------------------------------------------
void StringType::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
	wchar_t* PyUnicode_AsWideCharStringRet0 = PyUnicode_AsWideCharString(pyValue, NULL);
	char* ccattr = wchar2char(PyUnicode_AsWideCharStringRet0);
	PyMem_Free(PyUnicode_AsWideCharStringRet0);

	(*mstream) << ccattr;
	free(ccattr);
}

//-------------------------------------------------------------------------------------
PyObject* StringType::createFromStream(MemoryStream* mstream)
{
	std::string val = "";
	if(mstream)
		(*mstream) >> val;

	PyObject* pyobj = PyUnicode_FromString(val.c_str());

	if (pyobj && !PyErr_Occurred()) 
		return pyobj;

	::PyErr_PrintEx(0);

	return NULL;
}

//-------------------------------------------------------------------------------------
UnicodeType::UnicodeType(DATATYPE_UID did):
DataType(did)
{
}

//-------------------------------------------------------------------------------------
UnicodeType::~UnicodeType()
{
}

//-------------------------------------------------------------------------------------
bool UnicodeType::isSameType(PyObject* pyValue)
{
	if(pyValue == NULL)
	{
		OUT_TYPE_ERROR("UNICODE");
		return false;
	}

	bool ret = PyUnicode_Check(pyValue);
	if(!ret)
		OUT_TYPE_ERROR("UNICODE");
	return ret;
}

//-------------------------------------------------------------------------------------
PyObject* UnicodeType::parseDefaultStr(std::string defaultVal)
{
	PyObject* pyobj = PyUnicode_DecodeUTF8(defaultVal.data(), defaultVal.size(), "");

	if(pyobj && !PyErr_Occurred()) 
	{
		return pyobj;
	}

	PyErr_Clear();
	return PyUnicode_DecodeUTF8("", 0, "");
}

//-------------------------------------------------------------------------------------
void UnicodeType::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
	PyObject* pyobj = PyUnicode_AsUTF8String(pyValue);
	if(pyobj == NULL)
	{
		OUT_TYPE_ERROR("UNICODE");
		return;
	}	

	mstream->appendBlob(PyBytes_AS_STRING(pyobj), PyBytes_GET_SIZE(pyobj));
	Py_DECREF(pyobj);
}

//-------------------------------------------------------------------------------------
PyObject* UnicodeType::createFromStream(MemoryStream* mstream)
{
	std::string val = "";
	if(mstream)
	{
		mstream->readBlob(val);
	}

	PyObject* pyobj = PyUnicode_DecodeUTF8(val.data(), val.size(), "");

	if(pyobj && !PyErr_Occurred()) 
	{
		return pyobj;
	}

	::PyErr_PrintEx(0);
	return NULL;
}

//-------------------------------------------------------------------------------------
PythonType::PythonType(DATATYPE_UID did):
DataType(did)
{
}

//-------------------------------------------------------------------------------------
PythonType::~PythonType()
{
}

//-------------------------------------------------------------------------------------
bool PythonType::isSameType(PyObject* pyValue)
{
	if(pyValue == NULL)
	{
		OUT_TYPE_ERROR("PYTHON");
		return false;
	}

	bool ret = script::Pickler::pickle(pyValue).empty();
	if(ret)
		OUT_TYPE_ERROR("PYTHON");
	return !ret;
}

//-------------------------------------------------------------------------------------
PyObject* PythonType::parseDefaultStr(std::string defaultVal)
{
	std::string val = "";
	if(val.size() > 0)
	{
		PyObject* module = PyImport_AddModule("__main__");
		if(module == NULL)
		{
			PyErr_SetString(PyExc_SystemError, 
				"PythonType::createObject:PyImport_AddModule __main__ is error!");
			
			PyErr_PrintEx(0);	
			S_Return;
		}

		PyObject* mdict = PyModule_GetDict(module); // Borrowed reference.
		
		return PyRun_String(const_cast<char*>(val.c_str()), 
							Py_eval_input, mdict, mdict);
	}
		
	S_Return;
}

//-------------------------------------------------------------------------------------
void PythonType::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
	std::string sdata = script::Pickler::pickle(pyValue);
	
	uint32 length = sdata.length();
	(*mstream) << length;
	
	mstream->append(sdata.c_str(), length);
}

//-------------------------------------------------------------------------------------
PyObject* PythonType::createFromStream(MemoryStream* mstream)
{
	std::string val = "";
	uint8* udata = NULL;
	uint32 udataLen = 0;

	(*mstream) >> udataLen;
	
	udata = new uint8[udataLen + 1];
	
	mstream->read(udata, udataLen);
	
	val.assign((char*)udata, udataLen);
	
	SAFE_RELEASE_ARRAY(udata);
	
	return script::Pickler::unpickle(val);
}

//-------------------------------------------------------------------------------------
BlobType::BlobType(DATATYPE_UID did):
DataType(did)
{
}

//-------------------------------------------------------------------------------------
BlobType::~BlobType()
{
}

//-------------------------------------------------------------------------------------
bool BlobType::isSameType(PyObject* pyValue)
{
	if(pyValue == NULL)
	{
		OUT_TYPE_ERROR("BLOB");
		return false;
	}

	bool ret = PyBytes_Check(pyValue);
	if(!ret)
		OUT_TYPE_ERROR("BLOB");

	return ret;
}

//-------------------------------------------------------------------------------------
PyObject* BlobType::parseDefaultStr(std::string defaultVal)
{
	return PyBytes_FromString("");
}

//-------------------------------------------------------------------------------------
void BlobType::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
	char *buffer;
	Py_ssize_t length;

	if(PyBytes_AsStringAndSize(pyValue, &buffer, &length) < 0)
	{
		OUT_TYPE_ERROR("BLOB");
	}

	if(length > 0)
		mstream->append(buffer, length);
}

//-------------------------------------------------------------------------------------
PyObject* BlobType::createFromStream(MemoryStream* mstream)
{
	uint32 size = 0;
	std::string val = "";
	if(mstream)
	{
		(*mstream) >> size;
		val.assign((char*)(mstream->data() + mstream->rpos()), size);
		mstream->read_skip(size);
	}

	if(size == 0)
	{
		S_Return;
	}

	PyObject* pyobj = PyBytes_FromStringAndSize(val.data(), size);

	if (pyobj && !PyErr_Occurred())
	{
		return pyobj;
	}

	OUT_TYPE_ERROR("BLOB");
	return NULL;
}

//-------------------------------------------------------------------------------------
MailboxType::MailboxType(DATATYPE_UID did):
DataType(did)
{
}

//-------------------------------------------------------------------------------------
MailboxType::~MailboxType()
{
}

//-------------------------------------------------------------------------------------
bool MailboxType::isSameType(PyObject* pyValue)
{
	if(pyValue == NULL)
	{
		OUT_TYPE_ERROR("MAILBOX");
		return false;
	}

	bool ret = script::Pickler::pickle(pyValue).empty();
	if(ret)
		OUT_TYPE_ERROR("MAILBOX");
	return !ret;
}

//-------------------------------------------------------------------------------------
PyObject* MailboxType::parseDefaultStr(std::string defaultVal)
{
	Py_RETURN_NONE;
}

//-------------------------------------------------------------------------------------
void MailboxType::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
	mstream->appendBlob(script::Pickler::pickle(pyValue));
}

//-------------------------------------------------------------------------------------
PyObject* MailboxType::createFromStream(MemoryStream* mstream)
{
	std::string val = "";
	if(mstream)
	{
		mstream->readBlob(val);
	}
	else
		S_Return;	

	return script::Pickler::unpickle(val);
}

//-------------------------------------------------------------------------------------
FixedArrayType::FixedArrayType(DATATYPE_UID did):
DataType(did)
{
}

//-------------------------------------------------------------------------------------
FixedArrayType::~FixedArrayType()
{
	dataType_->decRef();
}

//-------------------------------------------------------------------------------------
PyObject* FixedArrayType::createNewItemFromObj(PyObject* pyobj)
{
	if(!isSameItemType(pyobj))
	{
		Py_RETURN_NONE;
	}

	return dataType_->createNewFromObj(pyobj);
}

//-------------------------------------------------------------------------------------
PyObject* FixedArrayType::createNewFromObj(PyObject* pyobj)
{
	if(!isSameType(pyobj))
	{
		Py_RETURN_NONE;
	}

	if(PyObject_TypeCheck(pyobj, FixedArray::getScriptType()))
	{
		return pyobj;
	}

	return new FixedArray(this, pyobj);
}

//-------------------------------------------------------------------------------------
bool FixedArrayType::initialize(XmlPlus* xmlplus, TiXmlNode* node)
{
	TiXmlNode* arrayNode = xmlplus->enterNode(node, "of");
	std::string strType = xmlplus->getValStr(arrayNode);
	//std::transform(strType.begin(), strType.end(), strType.begin(), toupper);										// 转换为大写

	if(strType == "ARRAY")
	{
		FixedArrayType* dataType = new FixedArrayType();
		if(dataType->initialize(xmlplus, arrayNode)){
			dataType_ = dataType;
			dataType_->incRef();
		}
	}
	else
	{
		DataType* dataType = DataTypes::getDataType(strType);
		if(dataType != NULL){
			dataType_ = dataType;
			dataType_->incRef();
		}
		else
		{
			ERROR_MSG("FixedArrayType::initialize: can't found type[%s] by key[%s].\n", 
				strType.c_str(), "ARRAY");
			
			return false;
		}			
	}
	return true;
}

//-------------------------------------------------------------------------------------
bool FixedArrayType::isSameItemType(PyObject* pyValue)
{
	return dataType_->isSameType(pyValue);
}

//-------------------------------------------------------------------------------------
bool FixedArrayType::isSameType(PyObject* pyValue)
{
	if(pyValue == NULL)
	{
		OUT_TYPE_ERROR("ARRAY");
		return false;
	}
	
	if(!PySequence_Check(pyValue))
	{
		OUT_TYPE_ERROR("ARRAY");
		return false;
	}

	Py_ssize_t size = PySequence_Size(pyValue);
	for(Py_ssize_t i=0; i<size; i++)
	{
		PyObject* pyVal = PySequence_GetItem(pyValue, i);
		bool ok = dataType_->isSameType(pyVal);
		Py_DECREF(pyVal);
		if(!ok)
			return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------
PyObject* FixedArrayType::parseDefaultStr(std::string defaultVal)
{
	return new FixedArray(this);
}

//-------------------------------------------------------------------------------------
void FixedArrayType::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
	ArraySize size = PySequence_Size(pyValue);
	(*mstream) << size;

	for(ArraySize i=0; i<size; i++)
	{
		PyObject* pyVal = PySequence_GetItem(pyValue, i);
		dataType_->addToStream(mstream, pyVal);
		Py_DECREF(pyVal);
	}
}

//-------------------------------------------------------------------------------------
PyObject* FixedArrayType::createFromStream(MemoryStream* mstream)
{
	ArraySize size;
	FixedArray* arr = new FixedArray(this);

	if(mstream)
	{
		(*mstream) >> size;	
		
		for(ArraySize i=0; i<size; i++)
		{
			PyObject* pyVal = dataType_->createFromStream(mstream);

			std::vector<PyObject*>& vals = arr->getValues();
			vals.push_back(pyVal);
		}
	}

	return arr;
}

//-------------------------------------------------------------------------------------
FixedDictType::FixedDictType(DATATYPE_UID did):
DataType(did),
keyTypes_(),
implObj_(NULL),
pycreateObjFromDict_(NULL),
pygetDictFromObj_(NULL),
pyisSameType_(NULL),
moduleName_()
{
}

//-------------------------------------------------------------------------------------
FixedDictType::~FixedDictType()
{
	FIXEDDICT_KEYTYPE_MAP::iterator iter = keyTypes_.begin();
	for(; iter != keyTypes_.end(); iter++)
	{
		iter->second->dataType->decRef();
	}

	keyTypes_.clear();

	S_RELEASE(pycreateObjFromDict_);
	S_RELEASE(pygetDictFromObj_);
	S_RELEASE(pyisSameType_);
	S_RELEASE(implObj_);
}

//-------------------------------------------------------------------------------------
std::string FixedDictType::getKeyNames(void)
{
	std::string keyNames = "";

	FIXEDDICT_KEYTYPE_MAP::iterator iter = keyTypes_.begin();
	for(; iter != keyTypes_.end(); iter++)
	{
		keyNames += iter->first + ",";
	}

	return keyNames;
}

//-------------------------------------------------------------------------------------
PyObject* FixedDictType::createNewItemFromObj(const char* keyName, PyObject* pyobj)
{
	DataType* dataType = isSameItemType(keyName, pyobj);
	if(!dataType)
	{
		Py_RETURN_NONE;
	}

	FIXEDDICT_KEYTYPE_MAP::iterator iter = keyTypes_.begin();
	for(; iter != keyTypes_.end(); iter++)
	{
		if(iter->first == keyName)
		{
			return iter->second->dataType->createNewFromObj(pyobj);
		}
	}

	Py_RETURN_NONE;
}

//-------------------------------------------------------------------------------------
PyObject* FixedDictType::createNewFromObj(PyObject* pyobj)
{
	if(!isSameType(pyobj))
	{
		Py_RETURN_NONE;
	}

	if(PyObject_TypeCheck(pyobj, FixedDict::getScriptType()))
	{
		if(this->hasImpl())
		{
			return impl_createObjFromDict(static_cast<FixedDict*>(pyobj)->getDictObject());
		}

		return pyobj;
	}
	
	if(this->hasImpl())
	{
		return impl_createObjFromDict(pyobj);
	}

	return new FixedDict(this, pyobj);
}

//-------------------------------------------------------------------------------------
bool FixedDictType::initialize(XmlPlus* xmlplus, TiXmlNode* node)
{
	TiXmlNode* propertiesNode = xmlplus->enterNode(node, "Properties");
	std::string strType = "", typeName = "";
	
	XML_FOR_BEGIN(propertiesNode)
	{
		typeName = xmlplus->getKey(propertiesNode);

		TiXmlNode* typeNode = xmlplus->enterNode(propertiesNode->FirstChild(), "Type");
		TiXmlNode* PersistentNode = xmlplus->enterNode(propertiesNode->FirstChild(), "Persistent");
		
		bool persistent = true;
		if(PersistentNode)
		{
			std::string strval = xmlplus->getValStr(PersistentNode);
			if(strval == "false")
			{
				persistent = false;
			}
		}

		if(typeNode)
		{
			strType = xmlplus->getValStr(typeNode);
			//std::transform(strType.begin(), strType.end(), strType.begin(), toupper);										// 转换为大写

			if(strType == "ARRAY")
			{
				FixedArrayType* dataType = new FixedArrayType();
				DictItemDataType* pDictItemDataType = new DictItemDataType();
				pDictItemDataType->dataType = dataType;

				if(dataType->initialize(xmlplus, typeNode))
				{
					keyTypes_.push_back(std::make_pair(typeName, pDictItemDataType));
					dataType->incRef();

					if(dataType->getDataType()->type() == DATA_TYPE_MAILBOX)
						persistent = false;

					pDictItemDataType->persistent = persistent;
				}
				else
				{
					ERROR_MSG("FixedDictType::initialize: can't found array type[%s] by key[%s].\n", 
						strType.c_str(), typeName.c_str());

					delete pDictItemDataType;
					return false;
				}
			}
			else
			{
				DataType* dataType = DataTypes::getDataType(strType);
				DictItemDataType* pDictItemDataType = new DictItemDataType();
				pDictItemDataType->dataType = dataType;

				if(dataType != NULL)
				{
					keyTypes_.push_back(std::make_pair(typeName, pDictItemDataType));
					dataType->incRef();
					
					if(dataType->type() == DATA_TYPE_MAILBOX)
						persistent = false;

					pDictItemDataType->persistent = persistent;
				}
				else
				{
					ERROR_MSG("FixedDictType::initialize: can't found type[%s] by key[%s].\n", 
						strType.c_str(), typeName.c_str());
					
					delete pDictItemDataType;
					return false;
				}
			}
		}
	}
	XML_FOR_END(propertiesNode);

	if(g_componentType == CELLAPP_TYPE || g_componentType == BASEAPP_TYPE ||
		g_componentType == CLIENT_TYPE)
	{
		TiXmlNode* implementedByNode = xmlplus->enterNode(node, "implementedBy");
		if(implementedByNode)
		{
			strType = xmlplus->getValStr(implementedByNode);
			if(strType.size() > 0 && !loadImplModule(strType))
				return false;

			moduleName_ = strType;
		}
	}

	return true;
}

//-------------------------------------------------------------------------------------
bool FixedDictType::loadImplModule(std::string moduleName)
{
	KBE_ASSERT(implObj_ == NULL);
	
	std::vector<std::string> res_;
	kbe_split<char>(moduleName, '.', res_);
	
	if(res_.size() != 2)
	{
		ERROR_MSG("FixedDictType::loadImplModule: %s impl is error! like:[moduleName.inst]\n", 
			moduleName.c_str());
		return false;
	}

	PyObject* implModule = PyImport_ImportModule(res_[0].c_str());
	if (!implModule)
	{
		SCRIPT_ERROR_CHECK();
		return false;
	}
	
	implObj_ = PyObject_GetAttrString(implModule, res_[1].c_str());
	Py_DECREF(implModule);

	if (!implObj_)
	{
		SCRIPT_ERROR_CHECK()
		return false;
	}

	pycreateObjFromDict_ = PyObject_GetAttrString(implObj_, "createObjFromDict");
	if (!pycreateObjFromDict_)
	{
		SCRIPT_ERROR_CHECK()
		return false;
	}
	

	pygetDictFromObj_ = PyObject_GetAttrString(implObj_, "getDictFromObj");
	if (!pygetDictFromObj_)
	{
		SCRIPT_ERROR_CHECK()
		return false;
	}
	
	pyisSameType_ = PyObject_GetAttrString(implObj_, "isSameType");
	if (!pyisSameType_)
	{
		SCRIPT_ERROR_CHECK()
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------
PyObject* FixedDictType::impl_createObjFromDict(PyObject* dictData)
{
	PyObject* pyRet = PyObject_CallFunction(pycreateObjFromDict_, 
		const_cast<char*>("(O)"), dictData);
	
	if(pyRet == NULL)
	{
		SCRIPT_ERROR_CHECK();
	}
	
	if(!impl_isSameType(pyRet))
	{
		ERROR_MSG("FixedDictType::impl_createObjFromDict: %s.isSameType() is failed!\n", 
			moduleName_.c_str());
		
		Py_RETURN_NONE;
	}

	return pyRet;
}

//-------------------------------------------------------------------------------------
PyObject* FixedDictType::impl_getDictFromObj(PyObject* pyobj)
{
	PyObject* pyRet = PyObject_CallFunction(pygetDictFromObj_, 
		const_cast<char*>("(O)"), impl_createObjFromDict(pyobj));
	
	if(pyRet == NULL)
	{
		SCRIPT_ERROR_CHECK();
	}

	return pyRet;
}

//-------------------------------------------------------------------------------------
bool FixedDictType::impl_isSameType(PyObject* pyobj)
{
	PyObject* pyRet = PyObject_CallFunction(pyisSameType_, 
		const_cast<char*>("(O)"), pyobj);
	
	if(pyRet == NULL)
	{
		SCRIPT_ERROR_CHECK();
	}
	
	bool ret = Py_True == pyRet;
	Py_DECREF(pyRet);
	return ret;
}

//-------------------------------------------------------------------------------------
DataType* FixedDictType::isSameItemType(const char* keyName, PyObject* pyValue)
{
	FIXEDDICT_KEYTYPE_MAP::iterator iter = keyTypes_.begin();
	for(; iter != keyTypes_.end(); iter++)
	{
		if(iter->first == keyName)
		{
			if(pyValue == NULL || !iter->second->dataType->isSameType(pyValue))
			{
				PyErr_Format(PyExc_TypeError, 
					"set FIXED_DICT(%s) is error! at key: %s, keyNames=[%s].", 
					this->aliasName(), iter->first.c_str(), 
					getKeyNames().c_str());
				
				PyErr_PrintEx(0);
				return NULL;
			}
			else
			{
				return iter->second->dataType;
			}
		}
	}

	return NULL;
}

//-------------------------------------------------------------------------------------
bool FixedDictType::isSameType(PyObject* pyValue)
{
	if(pyValue == NULL)
	{
		OUT_TYPE_ERROR("DICT");
		return false;
	}

	if(PyObject_TypeCheck(pyValue, FixedDict::getScriptType()))
	{
		if(static_cast<FixedDict*>(pyValue)->getDataType()->id() == this->id())
			return true;
		else
			return false;
	}

	if(!PyDict_Check(pyValue))
	{
		OUT_TYPE_ERROR("DICT");
		return false;
	}

	Py_ssize_t dictSize = PyDict_Size(pyValue);
	if(dictSize != (Py_ssize_t)keyTypes_.size())
	{
		PyErr_Format(PyExc_TypeError, 
			"FIXED_DICT key no match. size:%d-%d, keyNames=[%s].", 
			dictSize, keyTypes_.size(), 
			getKeyNames().c_str());
		
		PyErr_PrintEx(0);
		return false;
	}

	FIXEDDICT_KEYTYPE_MAP::iterator iter = keyTypes_.begin();
	for(; iter != keyTypes_.end(); iter++)
	{
		PyObject* pyObject = PyDict_GetItemString(pyValue, const_cast<char*>(iter->first.c_str()));
		if(pyObject == NULL || !iter->second->dataType->isSameType(pyObject))
		{
			PyErr_Format(PyExc_TypeError, 
				"set FIXED_DICT(%s) is error! at key: %s, keyNames=[%s].", 
				this->aliasName(), iter->first.c_str(), 
				getKeyNames().c_str());
			
			PyErr_PrintEx(0);
			return false;
		}
	}
	
	return true;
}

//-------------------------------------------------------------------------------------
PyObject* FixedDictType::parseDefaultStr(std::string defaultVal)
{
	PyObject* val = PyDict_New();

	FIXEDDICT_KEYTYPE_MAP::iterator iter = keyTypes_.begin();
	for(; iter != keyTypes_.end(); iter++)
	{
		PyObject* item = iter->second->dataType->parseDefaultStr("");
		PyDict_SetItemString(val, iter->first.c_str(), item);
		Py_DECREF(item);
	}

	return new FixedDict(this, val);
}

//-------------------------------------------------------------------------------------
void FixedDictType::addToStream(MemoryStream* mstream, PyObject* pyValue)
{
	addToStreamEx(mstream, pyValue, false);
}

//-------------------------------------------------------------------------------------
void FixedDictType::addToStreamEx(MemoryStream* mstream, PyObject* pyValue, bool onlyPersistents)
{
	if(hasImpl())
	{
		pyValue = impl_getDictFromObj(pyValue);
	}

	PyObject* pydict = pyValue;
	if(PyObject_TypeCheck(pyValue, FixedDict::getScriptType()))
	{
		pydict = static_cast<FixedDict*>(pyValue)->getDictObject();
	}
	
	FIXEDDICT_KEYTYPE_MAP::iterator iter = keyTypes_.begin();

	for(; iter != keyTypes_.end(); iter++)
	{
		if(onlyPersistents)
		{
			if(!iter->second->persistent)
				continue;
		}

		PyObject* pyObject = 
			PyDict_GetItemString(pydict, const_cast<char*>(iter->first.c_str()));
		
		KBE_ASSERT(pyObject != NULL);
		iter->second->dataType->addToStream(mstream, pyObject);
	}

	if(hasImpl())
	{
		Py_DECREF(pyValue);
	}
}

//-------------------------------------------------------------------------------------
PyObject* FixedDictType::createFromStream(MemoryStream* mstream)
{
	FixedDict* pydict = new FixedDict(this, mstream);

	if(hasImpl())
	{
		PyObject* pyValue = impl_createObjFromDict(pydict);
		Py_DECREF(pydict);
		return pyValue;
	}

	return pydict;
}

//-------------------------------------------------------------------------------------
}
