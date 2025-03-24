#pragma once

#include <HyperReal/HyperRealCommon.h>

class HyperRealWindow;

class libHyperReal
{
public:
	static libHyperReal& GetInstance()
	{
		static libHyperReal instance;
		return instance;
	}

	void Initialize(ui32 width, ui32 height);
	void Terminate();

	void Run();

	//template<typename T>
	//set<T*> GetInstances()
	//{
	//	return GetInstancesOfType<T>(typeid(T));
	//}

	//template<typename T>
	//T* GetFirstInstance()
	//{
	//	auto instances = GetInstancesOfType<T>(typeid(T));
	//	if (instances.empty()) return nullptr;
	//	else return *instances.begin();
	//}

	//template <typename T, typename... Args>
	//T* CreateInstance(const string& name = "", Args&&... args)
	//{
	//	auto instance = new T(forward<Args>(args)...);
	//	instance->SetName(name);
	//	//objectInstances.push_back(instance);
	//	//s_instanceMap[typeid(T)].push_back(instance);
	////	return instance;
	////}

	////static unordered_map<type_index, vector<HyperRealObject*>>& GetInstanceMap();
	////static set<HyperRealObject*> GetAllInstances();

	//template<typename T>
	//static set<T*> GetInstancesOfType(type_index baseType)
	//{
	//	set<T*> instances;

	//	if (s_instanceMap.find(baseType) != s_instanceMap.end())
	//	{
	//		for (auto obj : s_instanceMap[baseType])
	//		{
	//			if (auto castedObj = dynamic_cast<T*>(obj))
	//			{
	//				instances.insert(castedObj);
	//			}
	//		}
	//	}

	//	for (const auto& subclass : HyperRealObject::GetAllSubclasses(baseType))
	//	{
	//		if (s_instanceMap.find(subclass) != s_instanceMap.end())
	//		{
	//			for (auto obj : s_instanceMap[subclass])
	//			{
	//				if (auto castedObj = dynamic_cast<T*>(obj))
	//				{
	//					instances.insert(castedObj);
	//				}
	//			}
	//		}
	//	}

	//	return instances;
	//}

	inline HyperRealWindow* GetHyperRealWindow() const { return hyperRealWindow; }

private:
	static libHyperReal* s_instance;

	libHyperReal();
	~libHyperReal();

	HyperRealWindow* hyperRealWindow = nullptr;
};