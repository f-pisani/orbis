#ifndef GAMESTRUCT_HPP_INCLUDED
#define GAMESTRUCT_HPP_INCLUDED

struct GameStats
{
	GameStats() : score(0) {}
	int score; // Score
};

class Bullet
{
	public:
		Bullet(int t, float a, sf::Vector2f p)
		: m_time(t), m_angle(a), m_position(p){}

		inline int time(){ return m_time; }
		inline float angle(){ return m_angle; }
		inline sf::Vector2f position(){ return m_position; }

		inline void setPosition(float x, float y){ m_position = sf::Vector2f(x, y); }

	private:
		int m_time;
		float m_angle;
		sf::Vector2f m_position;
};

class Invader
{
	public:
		Invader(int t, float a, sf::Vector2f p, int s, float r, int sc)
		: m_time(t), m_angle(a), m_position(p), m_speed(s), m_rotation(r), m_score(sc){}

		inline int time(){ return m_time; }
		inline float angle(){ return m_angle; }
		inline sf::Vector2f position(){ return m_position; }
		inline int speed(){ return m_speed; }
		inline float rotation(){ return m_rotation; }
		inline int score(){ return m_score; }

		inline void setPosition(sf::Vector2f p){ m_position = p; }
		inline void setRotation(float r){ m_rotation = r; }

	private:
		int m_time;
		float m_angle;
		sf::Vector2f m_position;
		int m_speed;
		float m_rotation;
		int m_score;
};

class SpawnRules
{
	public:
		SpawnRules(int tL, int sL, int sI, int iS, int iSc)
		: m_timeLimit(tL), m_spawnLimit(sL), m_spawnInterval(sI),
		m_invaderSpeed(iS), m_invaderScore(iSc){}

		inline int timeLimit(){ return m_timeLimit; }
		inline int spawnLimit(){ return m_spawnLimit; }
		inline int spawnInterval(){ return m_spawnInterval; }
		inline int invaderSpeed(){ return m_invaderSpeed; }
		inline int invaderScore(){ return m_invaderScore; }

	private:
		int m_timeLimit;
		int m_spawnLimit;
		int m_spawnInterval;
		int m_invaderSpeed;
		int m_invaderScore;
};

#endif // GAMESTRUCT_HPP_INCLUDED
