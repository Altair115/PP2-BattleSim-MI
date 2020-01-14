#pragma once

namespace BattleSim
{
//forward declarations
class Tank;
class Rocket;
class Smoke;
class Particle_beam;
class Grid;

class Game
{
  public:
    ~Game();
    void SetTarget(Surface* surface) { screen = surface; }
    void Init();
    void Shutdown();
    void Update(float deltaTime);
    void Draw();
    void Tick(float deltaTime);
    void MeasurePerformance();
    void UpdateTanks();
    void UpdateRockets();
    void UpdateParticalBeams();
    std::vector<LinkedList> BucketSort(std::vector<Tank*> &unsortedTanks,int numberofbuckets);
    void SortHealthBars();
    void DrawBlueHealth();
    void DrawRedHealth();
    void DrawHealthBars(int i, char color, int health);
    Tank& FindClosestEnemy(Tank& current_tank);

    void MouseUp(int button)
    { /* implement if you want to detect mouse button presses */
    }

    void MouseDown(int button)
    { /* implement if you want to detect mouse button presses */
    }

    void MouseMove(int x, int y)
    { /* implement if you want to detect mouse movement */
    }

    void KeyUp(int key)
    { /* implement if you want to handle keys */
    }

    void KeyDown(int key)
    { /* implement if you want to handle keys */
    }

  private:
    Surface* screen;

    vector<Tank> tanks;
    vector<Rocket> rockets;
    vector<Smoke> smokes;
    vector<Explosion> explosions;
    vector<Particle_beam> particle_beams;
    vector<Tank*> blueTanks;
    vector<Tank*> redTanks;

    Font* frame_count_font;
    long long frame_count = 0;
    Grid grid;
    bool lock_update = false;
};

}; // namespace BattleSim