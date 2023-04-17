//
// Created by ksiks_wa3r on 4/11/23.
//

#include "ParticleEmitter.h"

namespace ASEngine {

	ParticleEmitter::ParticleEmitter() {

	}

	ParticleEmitter::~ParticleEmitter() {
		particles.clear();
	}

	//add particle
	void ParticleEmitter::addParticle() {
		//set position
		float positionAngle = Random::rand_rangef(0.0f, 2.0f * M_PI);
		float positionRadius = Random::rand_rangef(0.0f, emitionRadius);
		particles[currentParticlesNumber].position = position + vec2::one().rotate(positionAngle) * positionRadius;

		//set velocity
		float velocity = Random::rand_rangef(particleDescriptor->velocity.min, particleDescriptor->velocity.max);
		float direction =  Random::rand_rangef(particleDescriptor->direction.min, particleDescriptor->direction.max);
		particles[currentParticlesNumber].velocity = vec2::one().rotate(direction) * velocity;

		//set angle
		particles[currentParticlesNumber].angle = Random::rand_rangef(particleDescriptor->angle.min, particleDescriptor->angle.max);

		//set frame
		float frame = Random::rand_rangef(particleDescriptor->frame.min, particleDescriptor->frame.max);
		particles[currentParticlesNumber].frame = uint32_t (float(Sprite(spriteId).frames) * frame);

		//set frame rate
		float frameRate = Random::rand_rangef(particleDescriptor->frameRate.min, particleDescriptor->frameRate.max);
		particles[currentParticlesNumber].frameRate = frameRate;

		currentParticlesNumber++;
	}

	//start emition
	void ParticleEmitter::emit() {
		particles.resize(particlesNumber);
		currentParticlesNumber = 0;
		emitted = true;
		time = 0.0f;
		addParticle();
	}

	//next step of particles
	void ParticleEmitter::update(float delta) {
		//update time
		time += delta;
		//time pass lifetime
		if (time > life) {
			emitted = false;
			return;
		}
		//ALOG("%f %f",time , float(currentParticlesNumber) * life / float(particlesNumber));
		//add particle
		while (emitted && time > float(currentParticlesNumber) * (life * (1.0f - explosiveness)) / float(particlesNumber) && currentParticlesNumber < particlesNumber) {
			addParticle();
		}

		//update particles params
		for (int i = 0; i < currentParticlesNumber; i++)  {
			//update position
			particles[i].position = particles[i].position + particles[i].velocity * delta;
			//update frame rate
			particles[i].frame += particles[i].frameRate * delta;
			//check animation loop
			if (!isSpriteAnimationLoop)
				particles[i].frame = fmin(particles[i].frame, float(Sprite(spriteId).frames - 1) );

		}

	}

	//draw particles
	void ParticleEmitter::draw(Graphics &graphics) {
		//time pass lifetime
		if (time > life)
			return;
		//particles  draw
		for (int i = 0; i < currentParticlesNumber; i++) {
			graphics.drawSprite(spriteId, uint32_t(particles[i].frame), particles[i].position, vec2::one(), particles[i].angle, Color::white);
		}
	}


} // ASEngine