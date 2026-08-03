#include "pch.h"
#include "ParticleSystem.h"
#include "Engine.h"

namespace bad {
	bool ParticleSystem::Initialize(size_t size)
	{
		// reserve # particles in container
		m_particles.resize(size);

		return true;
	}

	void ParticleSystem::Shutdown()
	{
		// clear all particles
		m_particles.clear();
	}
	void ParticleSystem::Update()
	{
		// update active particles
		for (auto& particle : m_particles)
		{
			if (!particle.active) continue;

			// reduce particle.lifespan by subtracting delta time
			particle.lifespan -= g_time.GetDeltaTime();

			// set active if (particle.lifespan > 0);
			particle.active = (particle.lifespan > 0);

			// update position with velocity (multiply by dt)
			particle.position += particle.velocity * g_time.GetDeltaTime();
		}
	}

	void ParticleSystem::Draw()
	{
		// draw all active particlee
		for (auto& particle : m_particles)
		{
			if (particle.active)
			{
				// set particle color and draw point at current position
				Engine::Get().GetRenderer().DrawModel(particle.model, { particle.position, 0, {0.5f,0.5f} });
			}
		}
	}
	void ParticleSystem::AddParticle(const Particle& particle)
	{
		// get free particle
		Particle* freeParticle = GetFreeParticle();
		// check if free particle is not nullptr
		if (freeParticle)
		{
			// set free particle object with particle
			*freeParticle = particle;
			// set particle active
			freeParticle->active = true;
		}
	}

	Particle* ParticleSystem::GetFreeParticle()
	{
		// find and return inactive particle 
		for (auto& particle : m_particles)
		{
			// return pointer to inactive particle
			if (!particle.active)
				return &particle;
		}

		// no free particles, return nullptr
		return nullptr;
	}
}