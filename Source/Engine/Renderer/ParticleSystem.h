#pragma once
#include "Math/Color.h"
#include <vector>
#include "Model.h"

namespace bad {
	struct Particle {
		bool active{ false };
		float lifespan{ 1 };
		Vector2<float> position{ 0,0 };
		Vector2<float> velocity{ 0,0 };
		void SetColor(const Color8& color) { model.GetMesh(0).SetColor(color); }
		Color8 color;
		Model model{
			{
				Mesh{
					{
						{-1,-1},{-1,1},{1,0 }, {-1,-1}
					},
					color
				}
			}
		};
	};
	class ParticleSystem {
	public:
		ParticleSystem() = default;

		bool Initialize(size_t poolSize = 1000);
		void Shutdown();

		void Update();
		void Draw() const;

		void AddParticle(const Particle& particle);

	private:
		Particle* GetFreeParticle();

	private:
		// store particles in particle pool
		std::vector<Particle> m_particles;
	};
}