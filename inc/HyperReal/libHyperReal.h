#pragma once

#include <HyperReal/HyperRealCommon.h>
#include <HyperReal/HyperRealWindow.h>

#include <HyperReal/Systems/Systems.h>
#include <HyperReal/Components/Components.h>

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

	inline HyperRealWindow* GetHyperRealWindow() const { return hyperRealWindow; }

	inline Registry& GetRegistry() { return registry; }

	inline Camera* GetActiveCamera() { return activeCamera; }
	inline void SetActiveCamera(Camera* camera) { activeCamera = camera; }

#pragma region Entity
	inline Entity CreateEntity() { return registry.create(); }
	inline void RemoveEntity(Entity entity) { registry.destroy(entity); }
#pragma endregion

#pragma region Component
	template<typename T, typename ...Args> T& CreateComponent(Entity entity, Args&&... args)
	{
		auto& t = registry.emplace<T>(entity, forward<Args>(args)...);
		return t;
	}

	template<typename T> T& GetComponent(Entity entity)
	{
		return registry.get<T>(entity);
	}

	template<typename T> void RemoveComponent(Entity entity)
	{
		registry.remove<T>(entity);
	}

	template<typename T> bool HasComponent(Entity entity)
	{
		return registry.any_of<T>(entity);
	}
#pragma endregion

#pragma region Event
	template<typename T, typename... Args>
	void RegisterEvent(Entity entity, function<void(Entity, Args&&...)> callback)
	{
		auto& map = GetOrCreateEntityCallbackMap<T, Args...>();
		map[entity] = move(callback);
	}

	template<typename T>
	void RegisterEvent(Entity entity, std::function<void(Entity, T&&)> callback)
	{
		RegisterEvent<T, T>(entity, std::move(callback));
	}

	template<typename T, typename... Args>
	void UnregisterEvent(Entity entity)
	{
		auto it = entityCallbackStorage.find(type_index(typeid(tuple<T, Args...>)));
		if (it != entityCallbackStorage.end())
		{
			auto& map = *any_cast<unordered_map<Entity, function<void(Entity, Args&&...)>>>(&it->second);
			map.erase(entity);
		}
	}

	template<typename T, typename... Args>
	void DispatchEvent(Args&&... args)
	{
		auto& map = GetOrCreateEntityCallbackMap<T, Args...>();
		for (auto& [entity, callback] : map)
		{
			callback(entity, forward<Args>(args)...);
		}
	}

	template<typename T, typename... Args>
	void DispatchEvent(Entity entity, Args&&... args)
	{
		auto& map = GetOrCreateEntityCallbackMap<T, Args...>();
		auto it = map.find(entity);
		if (it != map.end()) {
			it->second(entity, forward<Args>(args)...);
		}
	}

	inline void ClearAllEvents() { entityCallbackStorage.clear(); }
#pragma endregion

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
	static libHyperReal* s_instance;

	libHyperReal();
	~libHyperReal();

	HyperRealWindow* hyperRealWindow = nullptr;
	Registry registry;

	Camera* activeCamera = nullptr;

	vector<ISystem*> systems;

#pragma region Event
	unordered_map<type_index, any> entityCallbackStorage;

	template<typename T, typename... Args>
	unordered_map<Entity, function<void(Entity, Args&&...)>>& GetOrCreateEntityCallbackMap()
	{
		using FuncType = std::function<void(Entity, Args&&...)>;
		using MapType = std::unordered_map<Entity, FuncType>;
		type_index key = typeid(tuple<T, Args...>);
		auto it = entityCallbackStorage.find(key);
		if (it == entityCallbackStorage.end())
		{
			entityCallbackStorage[key] = MapType{};
		}
		return *std::any_cast<MapType>(&entityCallbackStorage[key]);
	}

	unordered_map<type_index, any> componentCallbackStorage;

	template<typename T, typename... Args>
	unordered_map<T, function<void(Args&&...)>>& GetOrCreateComponentCallbackMap()
	{
		using FuncType = std::function<void(Args&&...)>;
		using MapType = std::unordered_map<T, FuncType>;
		type_index key = typeid(tuple<T, Args...>);
		auto it = componentCallbackStorage.find(key);
		if (it == componentCallbackStorage.end())
		{
			componentCallbackStorage[key] = MapType{};
		}
		return *std::any_cast<MapType>(&componentCallbackStorage[key]);
	}
#pragma endregion
};