#include "stdafx.h"
#include "utility.h"
#include "component.h"
#include "database.h"

//
//template <typename T>
//std::string ComponentType<T>::name = ToString(T);
//
//template <typename T>
//ComponentType<T> Component<T>::type;

int IContainer::containerIndex = 0;

DataBase::DataMap DataBase::datas;
