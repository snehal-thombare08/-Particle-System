#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstring>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

const int WIDTH = 1200, HEIGHT = 800;

float rF(float a, float b) { return a + (b-a)*(rand()/(float)RAND_MAX); }

struct Particle {
    float x, y, vx, vy;
    float life, maxLife;
    float size;
    sf::Color col;
    int type; // 0=fire 1=snow 2=explosion 3=galaxy 4=firework
};

std::vector<Particle> particles;
int emitMode = 0;
std::string modeNames[] = {"Fire","Snow","Explosion","Galaxy","Firework"};

void spawnFire(float mx, float my) {
    for(int i=0;i<8;i++){
        float life = rF(0.5f,1.5f);
        float angle = rF(-0.5f,0.5f) - 3.14159f*0.5f;
        float speed = rF(60,180);
        uint8_t r=255, g=(uint8_t)rF(80,200), b=0;
        particles.push_back({mx+rF(-10,10),my+rF(-5,5),
            std::cos(angle)*speed, std::sin(angle)*speed,
            life,life, rF(3,8), sf::Color(r,g,b,220), 0});
    }
}

void spawnSnow(float mx) {
    float life = rF(3.f,6.f);
    particles.push_back({mx, -10.f,
        rF(-20,20), rF(40,100),
        life,life, rF(2,5), sf::Color(220,235,255,200), 1});
}

void spawnExplosion(float mx, float my) {
    for(int i=0;i<80;i++){
        float angle = rF(0,6.28318f);
        float speed = rF(50,350);
        float life = rF(0.4f,1.2f);
        uint8_t r=(uint8_t)rF(180,255),g=(uint8_t)rF(50,200),b=(uint8_t)rF(0,80);
        particles.push_back({mx,my,
            std::cos(angle)*speed,std::sin(angle)*speed,
            life,life, rF(2,6), sf::Color(r,g,b,255), 2});
    }
}

void spawnGalaxy(float mx, float my) {
    for(int i=0;i<5;i++){
        float angle = rF(0,6.28318f);
        float r2 = rF(5,250);
        float speed = rF(20,80);
        float life = rF(2.f,5.f);
        uint8_t r=(uint8_t)rF(100,255),g=(uint8_t)rF(100,255),b=255;
        particles.push_back({mx+std::cos(angle)*r2*0.3f, my+std::sin(angle)*r2*0.3f,
            -std::sin(angle)*speed, std::cos(angle)*speed,
            life,life, rF(1,3), sf::Color(r,g,b,180), 3});
    }
}

void spawnFirework(float mx, float my) {
    // Trail up
    float life = rF(1.f,2.f);
    particles.push_back({mx,my, rF(-20,20),-rF(300,500),
        life,life, 4, sf::Color(255,220,100,255), 4});
    // Burst
    for(int i=0;i<120;i++){
        float angle = (float)i/120.f*6.28318f;
        float speed = rF(80,280);
        float flife = rF(0.5f,1.5f);
        uint8_t r=(uint8_t)rF(150,255),g=(uint8_t)rF(100,255),b=(uint8_t)rF(100,255);
        particles.push_back({mx,my,
            std::cos(angle)*speed,std::sin(angle)*speed,
            flife,flife, rF(2,4), sf::Color(r,g,b,255), 4});
    }
}

int main(){
    sf::RenderWindow window(
        sf::VideoMode({(unsigned)WIDTH,(unsigned)HEIGHT}),
        "Particle System | LMB:Emit | 1-5:Mode | Space:Clear | G:Gravity"
    );
    window.setFramerateLimit(60);
    srand((unsigned)time(0));

    bool gravity = true;
    bool lmb = false;
    float snowTimer = 0.f;
    float galaxyTimer = 0.f;

    sf::Font font; bool hf = font.openFromFile("C:/Windows/Fonts/arial.ttf");
    sf::Text hud(font); hud.setCharacterSize(15);
    hud.setFillColor(sf::Color::White);
    hud.setOutlineColor(sf::Color::Black); hud.setOutlineThickness(1.5f);
    hud.setPosition({8.f,8.f});

    sf::Clock clock;

    while(window.isOpen()){
        float dt = std::min(clock.restart().asSeconds(), 0.02f);
        auto mp = sf::Mouse::getPosition(window);

        snowTimer += dt;
        galaxyTimer += dt;

        while(auto ev = window.pollEvent()){
            if(ev->is<sf::Event::Closed>()) window.close();
            if(auto* k = ev->getIf<sf::Event::KeyPressed>()){
                if(k->code==sf::Keyboard::Key::Escape) window.close();
                if(k->code==sf::Keyboard::Key::Space) particles.clear();
                if(k->code==sf::Keyboard::Key::G) gravity=!gravity;
                if(k->code==sf::Keyboard::Key::Num1) emitMode=0;
                if(k->code==sf::Keyboard::Key::Num2) emitMode=1;
                if(k->code==sf::Keyboard::Key::Num3) emitMode=2;
                if(k->code==sf::Keyboard::Key::Num4) emitMode=3;
                if(k->code==sf::Keyboard::Key::Num5) emitMode=4;
            }
            if(auto* mb=ev->getIf<sf::Event::MouseButtonPressed>())
                if(mb->button==sf::Mouse::Button::Left) lmb=true;
            if(auto* mb=ev->getIf<sf::Event::MouseButtonReleased>())
                if(mb->button==sf::Mouse::Button::Left) lmb=false;
            if(auto* mb=ev->getIf<sf::Event::MouseButtonPressed>())
                if(mb->button==sf::Mouse::Button::Right){
                    if(emitMode==2) spawnExplosion((float)mp.x,(float)mp.y);
                    if(emitMode==4) spawnFirework((float)mp.x,(float)mp.y);
                }
        }

        // Emit
        if(lmb){
            if(emitMode==0) spawnFire((float)mp.x,(float)mp.y);
            if(emitMode==2) spawnExplosion((float)mp.x,(float)mp.y);
            if(emitMode==3 && galaxyTimer>0.05f){ spawnGalaxy((float)mp.x,(float)mp.y); galaxyTimer=0; }
            if(emitMode==4) spawnFirework((float)mp.x,(float)mp.y);
        }
        if(emitMode==1 && snowTimer>0.05f){
            spawnSnow(rF(0,(float)WIDTH)); snowTimer=0;
        }

        // Update particles
        for(auto& p : particles){
            p.life -= dt;
            float grav = gravity ? 150.f : 0.f;
            if(p.type==0) grav = -60.f; // fire rises
            if(p.type==1) grav = 80.f;  // snow falls
            if(p.type==3) grav = 0.f;   // galaxy no gravity

            p.vy += grav * dt;
            if(p.type==1) p.vx += rF(-20,20)*dt; // snow drift
            p.x += p.vx*dt;
            p.y += p.vy*dt;

            // Fade
            float alpha = p.life/p.maxLife;
            p.col.a = (uint8_t)(alpha*255);
            if(p.type==0){
                p.col.g = (uint8_t)(alpha*200);
                p.col.r = 255;
            }
        }

        // Remove dead
        particles.erase(std::remove_if(particles.begin(),particles.end(),
            [](const Particle& p){ return p.life<=0 || p.x<-50||p.x>WIDTH+50||p.y>HEIGHT+50||p.y<-200; }),
            particles.end());

        // Draw
        window.clear(sf::Color(8,10,20));

        sf::CircleShape cs;
        for(auto& p : particles){
            float s = p.size * 2.f * (p.life/p.maxLife * 0.5f + 0.5f);
            cs.setRadius(s);
            cs.setOrigin({s,s});
            cs.setPosition({p.x,p.y});
            cs.setFillColor(p.col);
            window.draw(cs);
        }

        if(hf){
            hud.setString("Mode: " + modeNames[emitMode] +
                "  |  1:Fire 2:Snow 3:Explosion 4:Galaxy 5:Firework" +
                "  |  LMB:Emit RMB:Burst  G:Gravity(" + std::string(gravity?"ON":"OFF") + ")" +
                "  |  Particles:" + std::to_string(particles.size()) +
                "  |  Space:Clear");
            window.draw(hud);
        }
        window.display();
    }
    return 0;
}




