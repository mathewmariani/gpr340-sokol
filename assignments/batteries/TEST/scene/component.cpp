#include "component.h"
#include "../engine.h"

namespace
{
	struct component_factory_register : public template_factory_register<ComponentFactory::ComponentFactoryFunction, component_factory_register>
	{
	};

	component_factory_register begin;
}

ComponentFactory ComponentFactory::instance;
ComponentFactory *ComponentFactory::getInstance()
{
	return &instance;
}

void ComponentFactory::Initialize()
{
	ConvertListToMap(&begin, functions);
}

void ComponentFactory::RegisterComponentFactory(ComponentFactoryFunction factory, const std::string &name)
{
	RegisterFactory(&begin, factory, name);
}

Component *ComponentFactory::CreateComponentByName(const std::string &name)
{
	if (functions[name] == 0)
	{
		return nullptr;
	}

	ComponentFactoryFunction func = functions[name];
	return func();
}