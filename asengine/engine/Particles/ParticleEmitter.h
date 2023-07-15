//
// Created by ksiks_wa3r on 4/11/23.
//

#ifndef ASENGINE_PARTICLEEMITTER_H
#define ASENGINE_PARTICLEEMITTER_H

#include <vector>

#include "Particle.h"
#include "ParticleDescriptor.h"

#include "engine/Resource/ResourceManager.h"
#include "engine/Resource/Sprite.h"
#include "engine/Renderer/Texture.h"
#include "engine/Renderer/Graphics.h"
#include "engine/Math/Random.h"

namespace ASEngine {

	class ParticleEmitter {
	public:
		//emition params
		//explosiveness close to 1.0f means the particles are emitted at the same time
		float explosiveness = 0.0f;
		//is emitting once or repeating
		bool repeat = false;
		//lifetime in seconds
		float life = 1.0f;
		//emition radius
		float emitionRadius = 0.0f;
		//number of particles to generate
		uint32_t particlesNumber = 1;
		//emitter position
		vec2 position = vec2::zero();

		//particle desciptor
		ParticleDescriptor* particleDescriptor;

		//texture
		ResourceID spriteId;
		//sprite loop
		bool isSpriteAnimationLoop = false;
		//texture enabled
		bool textureEnabled = false;


		//functions
		//emit particles
		void emit();

		//update to next step
		void update(float delta);

		//draw particles
		void draw(Graphics& graphics);

		//constructors
		ParticleEmitter();

		//destructors
		~ParticleEmitter();


	private:
		//list of particles
		std::vector<Particle> particles = {};
		//current time for emitter
		float time = 0.0f;
		//is emitted
		bool emitted = false;
		//current particle number
		uint32_t currentParticlesNumber = 0;
		//add particle
		void addParticle();
	};

} // ASEngine

#endif //ASENGINE_PARTICLEEMITTER_H
