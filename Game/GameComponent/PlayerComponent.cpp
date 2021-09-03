#include "PlayerComponent.h"
#include "ProjectileComponent.h"
#include "Engine.h"

using namespace nc;

void PlayerComponent::Create()
{
	owner->scene->engine->Get<EventSystem>()->Subscribe("collision_enter", std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1), owner);
	owner->scene->engine->Get<EventSystem>()->Subscribe("collision_exit", std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1), owner);

	owner->scene->engine->Get<AudioSystem>()->AddAudio("hurt", "audio/hurt.wav");
	owner->scene->engine->Get<AudioSystem>()->AddAudio("coin", "audio/coin.wav");
}

PlayerComponent::~PlayerComponent()
{
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_enter", owner);
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_exit", owner);
}

void PlayerComponent::Update()
{
	Vector2 force = Vector2::zero;
	if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_A) == InputSystem::eKeyState::Held)
	{
		force.x -= speed;
	}

	if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_D) == InputSystem::eKeyState::Held)
	{
		force.x += speed;
	}

	/*if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_W) == InputSystem::eKeyState::Held)
	{
		force.y -= speed;
	}

	if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_S) == InputSystem::eKeyState::Held)
	{
		force.y += speed;
	}*/

	if (contacts.size() > 0 && owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == InputSystem::eKeyState::Pressed)
	{
		force.y -= 350;
	}

	if (owner->scene->engine->Get<InputSystem>()->GetButtonState(0) == InputSystem::eKeyState::Pressed) //GetButtonState(SDL_BUTTON_LEFT) == InputSystem::eKeyState::Pressed)
	{
		Vector2 direction = owner->scene->engine->Get<InputSystem>()->GetMousePosition() - owner->transform.position;

		auto projectile = nc::ObjectFactory::Instance().Create<nc::Actor>("Projectile");
		projectile->transform.position = owner->transform.position;
		projectile->transform.rotation = nc::RadToDeg(direction.Angle());
		projectile->GetComponent<ProjectileComponent>()->direction = direction.Normalized();

		owner->scene->AddActor(std::move(projectile));
	}

	PhysicsComponent* physicsComponent = owner->GetComponent<PhysicsComponent>();
	assert(physicsComponent);

	physicsComponent->ApplyForce(force);

	SpriteAnimationComponent* spriteAnimationComponent = owner->GetComponent<SpriteAnimationComponent>();
	assert(spriteAnimationComponent);
	if (physicsComponent->velocity.x > 0) spriteAnimationComponent->StartSequence("walk_right");
	else if (physicsComponent->velocity.x < 0) spriteAnimationComponent->StartSequence("walk_left");
	else spriteAnimationComponent->StartSequence("idle");
}

void PlayerComponent::OnCollisionEnter(const Event& event)
{
	void* p = std::get<void*>(event.data);
	Actor* actor = reinterpret_cast<Actor*>(p);

	if (istring_compare(actor->tag, "Ground"))
	{
		contacts.push_back(actor);
	}

	if (istring_compare(actor->tag, "Enemy"))
	{
		owner->scene->engine->Get<AudioSystem>()->PlayAudio("hurt");
		health -= 1;
		if (health <= 0)
		{
			owner->destroy = true;
		}
	}

	std::cout << actor->tag;
}

void PlayerComponent::OnCollisionExit(const Event& event)
{
	void* p = std::get<void*>(event.data);
	Actor* actor = reinterpret_cast<Actor*>(p);

	if (istring_compare(actor->tag, "ground"))
	{
		contacts.remove(actor);
	}
}

bool PlayerComponent::Write(const rapidjson::Value& value) const
{
	return false;
}

bool PlayerComponent::Read(const rapidjson::Value& value)
{
	JSON_READ(value, speed);
	JSON_READ(value, health);
	JSON_READ(value, jump);

	return true;
}
