//
// Created by ksiks_wa3r on 4/11/23.
//

#ifndef ANDROIDSIMPLEENGINE_PARTICLEEMITTER_H
#define ANDROIDSIMPLEENGINE_PARTICLEEMITTER_H

#include <vector>

#include "Particle.h"
#include "ParticleDescriptor.h"

#include "../Renderer/Texture.h"
#include "../Renderer/Graphics.h"
#include "../Math/Random.h"

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
		//number of particles to generate
		uint32_t particlesNumber = 1;
		//position
		vec2 position = vec2::zero();

		//particle desciptor
		ParticleDescriptor* particleDescriptor;

		//texture
		SpriteID spriteId;
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

#endif //ANDROIDSIMPLEENGINE_PARTICLEEMITTER_H
