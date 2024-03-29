#pragma once

#include <string>
#include <map>

#define DECLARE_COMPONENT(name) \
    private: \
		static const std::string __const_class_name;

#define REGISTER_COMPONENT(className, scriptName) \
	const std::string className::__const_class_name = #scriptName; \
	namespace { \
		Component* __CreateComponent##className() { \
			return new className(); \
		} \
		class __register##className { \
		public: \
			__register##className() { \
				ComponentFactory::RegisterComponentFactory( \
					*__CreateComponent##className, #scriptName); \
			} \
		}; \
		__register##className __g_instance##className; \
	}

// forward declaration
class Component;

class ComponentFactory {
	static ComponentFactory instance;
	ComponentFactory() = default;
	~ComponentFactory() = default;

public:
	static ComponentFactory *getInstance();

	void Initialize();

	// function pointer
	typedef Component* (*ComponentFactoryFunction)();

	static void RegisterComponentFactory(ComponentFactoryFunction factory, const std::string& name);
	Component* CreateComponentByName(const std::string& name);

private:
	std::map<std::string, ComponentFactoryFunction> functions;
};

class Component {
public:
    Component() = default;
};