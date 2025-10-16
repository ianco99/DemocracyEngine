#pragma once
#include "Utilities/Exports.h"

class Entity;

class EXPORT Component
{
public:
	explicit Component(Entity* entity);
	virtual ~Component() = 0;
	Entity* entity;

};