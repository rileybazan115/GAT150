//#include "Enemy.h"
//#include "Math/MathUtils.h"
//#include "Projectile.h"
//#include "Engine.h"
//#include "Player.h"
//
//void Enemy::Update(float dt)
//{
//	if (scene->GetActor<Player>())
//	{
//		//nc::Vector2 direction = scene->GetActor<Player>()->transform.position - transform.position;
//		//nc::Vector2 forward = nc::Vector2::Rotate(nc::Vector2::left, transform.rotation);
//
//		//float turnAngle = nc::Vector2::SignedAngle(forward, direction.Normalized());
//		//transform.rotation = transform.rotation + turnAngle + (2 * dt);
//		//transform.rotation = nc::Lerp(transform.rotation, transform.rotation + turnAngle, 2 * dt);
//
//		//float angle = nc::Vector2::Angle(forward, direction.Normalized());
//		transform.position += nc::Vector2::Rotate(nc::Vector2::right, transform.rotation) * speed * dt;
//		//fire
//		fireTimer -= dt;
//		if (fireTimer <= 0 )
//		{
//			fireTimer = fireRate;
//
//			nc::Transform t = transform;
//			t.scale = 0.5f;
//
//			std::unique_ptr<Projectile> projectile = (std::make_unique<Projectile>(t, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Textures/spaceMissiles_001.png", scene->engine->Get<nc::Renderer>()), 250));
//			projectile->tag = "Enemy";
//			scene->AddActor(std::move(projectile));
//		}
//	}
//
//	
//	//transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
//	//transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);
//
//	Actor::Update(dt);
//}
//
//void Enemy::OnCollision(Actor* actor)
//{
//	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Player")
//	{
//		destroy = true;
//		scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 3, 1, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Textures/particle02.png"), 50);		scene->engine->Get<nc::AudioSystem>()->PlayAudio("explosion");
//		scene->engine->Get<nc::AudioSystem>()->PlayAudio("explosion");
//
//		nc::Event event;
//		event.name = "AddPoints";
//		event.data = 300;
//		scene->engine->Get<nc::EventSystem>()->Notify(event);
//	}
//}
