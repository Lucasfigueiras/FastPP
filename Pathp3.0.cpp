#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

float distancia(int x1, int y1, int x2, int y2){        //função distância de ponto a ponto
    float p;
    p = sqrt(pow(float(x1-x2), 2)+pow(float(y1-y2),2));
    return p;
}

float distrp(int x1, int y1, int x2, int y2,int px, int py){    //função distância de ponto a reta
    float dist=0;
    dist= ((px*(y1-y2))+(py*(x2-x1))+((x1*y2)-(x2*y1)))/distancia(x1,y1,x2,y2);
    return dist;
}

int acharPonto(int x1, int y1, int x2, int y2,int px, int py,char c, int e){   //acha o novo ponto para desviar do obstáculo
    float m,d1,d2,ang,dist;
    int xm,ym,xm2,ym2;
    dist=distrp(x1,y1,x2,y2,px,py);
    if(x2 != x1){
       m=float(y2 - y1)/float(x2 - x1);
    }
    else m=0;
    if(m!=0)ang=atan(-1/m);
    xm = int(px - 40*cos(ang));
    ym = int(py - 40*sin(ang));
    xm2 = int(px + 40*cos(ang));
    ym2 = int(py + 40*sin(ang));
    if(e == 0){
        d1=abs(distrp(x1,y1,x2,y2,xm,ym));
        d2=abs(distrp(x1,y1,x2,y2,xm2,ym2));
    }
    else if(e == 1){
        d1=abs(distrp(x1,y1,x2,y2,xm2,ym2));
        d2=abs(distrp(x1,y1,x2,y2,xm,ym));
    }
    if(d1>d2){
        xm=xm2;
        ym=ym2;
        }
    if(c=='x')return xm;
    if(c=='y')return ym;

}

class obstacle {				//cria as classes obstáculo, jogador e bola
    float pos_x, pos_y;
    public:
    obstacle (float, float);
    float x() {return pos_x;}
    float y() {return pos_y;}
};
obstacle::obstacle(float x, float y){
    pos_x = x;
    pos_y = y;
}

class player {
    float pos_x, pos_y;
    public:
    player (float, float);
    float x() {return pos_x;}
    float y() {return pos_y;}
};
player::player(float x, float y){
    pos_x = x;
    pos_y = y;
}

class ball {
    float pos_x, pos_y;
    public:
    ball (float, float);
    float x() {return pos_x;}
    float y() {return pos_y;}
};
ball::ball(float x, float y){
    pos_x = x;
    pos_y = y;
}




int main (){
    int x,y,xm,ym,xm2,ym2,d,a,e,f=0,g=0,h,i,b=0,t=1,aux,aux2,obs,esp=0;        //inicializa variáveis
    float dist,m,ang,d1,d2,dist2,kt,d3,d4,d5,d6,rnovo=0;
    int adv[4][2];
    int pontos[12][2];
    int bolax,bolay,jogx,jogy,contornox,contornoy;

//g++ -o Pathp3.0 Pathp3.0.cpp -lsfml-window -lsfml-graphics -lsfml-system

    sf::RenderWindow window(sf::VideoMode(930, 630), "Path Planning");
    
    sf::RectangleShape rectangle(sf::Vector2f(930, 630));   //cria o campo
    rectangle.setFillColor(sf::Color(50, 200, 50));
    sf::VertexArray lines(sf::LinesStrip, 13);          
        lines[0].position = sf::Vector2f(15, 15);
        lines[1].position = sf::Vector2f(15, 615);
        lines[2].position = sf::Vector2f(915, 615);
        lines[3].position = sf::Vector2f(915, 215);
        lines[4].position = sf::Vector2f(815, 215);
        lines[5].position = sf::Vector2f(815, 415);
        lines[6].position = sf::Vector2f(915, 415);
        lines[7].position = sf::Vector2f(915, 15);
        lines[8].position = sf::Vector2f(15, 15);
        lines[9].position = sf::Vector2f(15, 215);
        lines[10].position = sf::Vector2f(115, 215);
        lines[11].position = sf::Vector2f(115, 415);
        lines[12].position = sf::Vector2f(15, 415);
    sf::CircleShape circle(5);
        circle.setFillColor(sf::Color::White);
        circle.setPosition(460,310);
    
    sf::CircleShape bola(5);                            //cria a bola
        bola.setFillColor(sf::Color(255,165,0));                

        bola.setPosition(460,310);
    sf::CircleShape circle2(15);                        //cria o player
        circle2.setFillColor(sf::Color::Red);
        circle2.setPosition(550,300);
        circle2.setOutlineColor(sf::Color::Black); d5=d2;
        circle2.setOutlineThickness(3);
    
    sf::CircleShape circle3(15);                        //cria os obstáculos
        circle3.setFillColor(sf::Color::Blue);
        circle3.setPosition(345,300);
        circle3.setOutlineColor(sf::Color::Black);
        circle3.setOutlineThickness(3);
    sf::CircleShape circle4(15);
        circle4.setFillColor(sf::Color::Blue);
        circle4.setPosition(300,300);
        circle4.setOutlineColor(sf::Color::Black);
        circle4.setOutlineThickness(3);
    sf::CircleShape circle5(15);
        circle5.setFillColor(sf::Color::Blue);
        circle5.setPosition(255,300);
        circle5.setOutlineColor(sf::Color::Black);
        circle5.setOutlineThickness(3);
    sf::CircleShape circle6(15);
        circle6.setFillColor(sf::Color::Blue);
        circle6.setPosition(210,300);
        circle6.setOutlineColor(sf::Color::Black);
        circle6.setOutlineThickness(3);
    sf::CircleShape circle7(15);
        circle7.setFillColor(sf::Color::Blue);
        circle7.setPosition(110,300);
        circle7.setOutlineColor(sf::Color::Black);
        circle7.setOutlineThickness(3);

    while(window.isOpen()){
        std::vector <obstacle> obst;          
        ball B(bola.getPosition().x + 5, bola.getPosition().y + 5);                  //centraliza as coordenadas de todos os objetos
        player P(circle2.getPosition().x + 15, circle2.getPosition().y + 15);
        obst.push_back(obstacle(circle3.getPosition().x + 15, circle3.getPosition().y + 15));
        obst.push_back(obstacle(circle4.getPosition().x + 15, circle4.getPosition().y + 15));
        obst.push_back(obstacle(circle5.getPosition().x + 15, circle5.getPosition().y + 15));
        obst.push_back(obstacle(circle6.getPosition().x + 15, circle6.getPosition().y + 15));
        

        sf::Event event;
        while (window.pollEvent(event)){                
            if (event.type == sf::Event::Closed){
                window.close();
			}
        
        if(event.type == sf::Event::MouseButtonPressed){                        //mexe os objetos com o mouse
            if((x>=B.x() - 5  && x<=B.x() + 5)&&(y>=B.y() - 5 && y<=B.y() + 5)){d=1;}
            if((x>=P.x() -15  && x<=P.x() + 15)&&(y>=P.y() - 15 && y<=P.y() + 15)){e=1;}
            if((x>=obst[0].x() - 15  && x<=obst[0].x() + 15)&&(y>=obst[0].y() - 15 && y<=obst[0].y() + 15)){f=1;}
            if((x>=obst[1].x() - 15  && x<=obst[1].x() + 15)&&(y>=obst[1].y() - 15 && y<=obst[1].y() + 15)){g=1;}
            if((x>=obst[2].x() - 15  && x<=obst[2].x() + 15)&&(y>=obst[2].y() - 15 && y<=obst[2].y() + 15)){h=1;}
            if((x>=obst[3].x() - 15  && x<=obst[3].x() + 15)&&(y>=obst[3].y() - 15 && y<=obst[3].y() + 15)){b=1;}
            }
        if(event.type == sf::Event::MouseButtonReleased){
            d=2;e=2;f=2;g=2;h=2;b=2;i=2;}
        if (event.type == sf::Event::MouseMoved)
            {
            x=event.mouseMove.x;
            y=event.mouseMove.y;
            }
        }

        pontos[0][0]=P.x();              //usa os pontos novos para calcular o melhor caminho
        pontos[0][1]=P.y();
        for(i=1;i<12;i++){pontos[i][0]=B.x();pontos[i][1]=B.y();}
        for(i=0;i<11;i++){
            d5=10000;
            for(aux=0;aux<4;aux++){
                d1=abs(distrp(pontos[i][0],pontos[i][1],B.x(),B.y(),obst[aux].x(),obst[aux].y()));      //distancia da reta de cada ponto até o objetivo em relação aos adversários
                d2=abs(distancia(pontos[i][0],pontos[i][1],obst[aux].x(),obst[aux].y()));               //distancia de cada ponto até os adversários
                d3=abs(distancia(pontos[i][0],pontos[i][1],B.x(),B.y()));                           //distancia de cada ponto até o objetivo
                d4=abs(distancia(B.x(),B.y(),obst[aux].x(),obst[aux].y()));                             //distancia do objetivo até os obstáculos
                if(d1<40 && (d2 < d3 && d4 < d3 ) && d2 <= d5){
                    pontos[i+1][0]= acharPonto(pontos[i][0],pontos[i][1],B.x(),B.y(),obst[aux].x(),obst[aux].y(),'x',0);   //acha a posição do novo ponto
                    pontos[i+1][1]= acharPonto(pontos[i][0],pontos[i][1],B.x(),B.y(),obst[aux].x(),obst[aux].y(),'y',0);
                    d5=d2;
                }
                for(aux2=0;aux2<4;aux2++){
                    if(aux2 != aux){
                        if(distancia(pontos[i+1][0],pontos[i+1][1],obst[aux2].x(),obst[aux2].y()) < 30){                              //acha a posição do novo ponto se dois obstáculos estiverem próximos
                            pontos[i+1][0]= acharPonto(pontos[i][0],pontos[i][1],B.x(),B.y(),obst[aux].x(),obst[aux].y(),'x',1);
                            pontos[i+1][1]= acharPonto(pontos[i][0],pontos[i][1],B.x(),B.y(),obst[aux].x(),obst[aux].y(),'y',1);
                            d5=d2;
                        }
                    }
                }
            }   
        }
                         
            
        
        sf::VertexArray trajetoria(sf::LinesStrip, i+1);
        
        for(aux=0;aux<i;aux++){
            trajetoria[aux].position = sf::Vector2f(pontos[aux][0], pontos[aux][1]);
            trajetoria[aux].color=sf::Color::Red;
        }
        trajetoria[i].position = sf::Vector2f(B.x(), B.y());
        trajetoria[i].color=sf::Color::Red;
        
        if(d==1){bola.setPosition(x-5,y-5);}            //centraliza os objetos no mouse enquanto estiverem se movendo
        if(e==1){circle2.setPosition(x-15,y-15);}
        if(f==1){circle3.setPosition(x-15,y-15);}
        if(g==1){circle4.setPosition(x-15,y-15);}
        if(h==1){circle5.setPosition(x-15,y-15);}
        if(b==1){circle6.setPosition(x-15,y-15);}
        
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(465, 15)),
            sf::Vertex(sf::Vector2f(465, 615))};
        
        window.clear();                     //desenha tudo
        window.draw(rectangle);
        window.draw(line, 5, sf::Lines);
        window.draw(circle);
        window.draw(lines);
        window.draw(circle3);
        window.draw(circle4);
        window.draw(circle5);
        window.draw(trajetoria);
        window.draw(circle2);
        window.draw(circle6);
        window.draw(bola);
        window.display();
    }
}
