#include "ProjectileComponent.h"
#include "Engine.h"

using namespace nc;

void ProjectileComponent::Create()
{
	owner->scene->engine->Get<EventSystem>()->Subscribe("collision_enter", std::bind(&ProjectileComponent::OnCollision, this, std::placeholders::_1), owner);
}

ProjectileComponent::~ProjectileComponent()
{
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_enter", owner);
}

void ProjectileComponent::Update()
{
	owner->GetComponent<PhysicsComponent>()->ApplyForce(direction * speed);
}

void ProjectileComponent::OnCollision(const nc::Event& event)
{
	void* p = std::get<void*>(event.data);
	Actor* actor = reinterpret_cast<Actor*>(p);

	if (istring_compare(actor->tag, "Ground"))
	{
		owner->destroy = true;
	}

	if (istring_compare(actor->tag, "Enemy"))
	{
		owner->destroy = true;

		Event event;
		event.name = "addScore";
		event.data = 10;

		owner->scene->engine->Get<EventSystem>()->Notify(event);
	}
}

bool ProjectileComponent::Write(const rapidjson::Value& value) const
{
	return false;
}

bool ProjectileComponent::Read(const rapidjson::Value& value)
{
	JSON_READ(value, speed);

	return true;
}