#include<SFML/Graphics.hpp>
#include<iostream>

#define CELL_SIZE 50

sf::RenderWindow window(sf::VideoMode(1000, 1000), "Life");

bool cells[1000/50][1000/50];
bool PAUSE = true;
//20x20

void draw_line(float x, float y, float x1, float y1)
{
    sf::Vertex line[2];
    line[0].position = sf::Vector2f(x, y);
    line[1].position = sf::Vector2f(x1, y1);
    window.draw(line, 2, sf::Lines);
}

void draw_grid()
{
    //Get window size
    sf::Vector2u size = window.getSize();
    //drawing x lines
    for(int i = 0; i<size.x; i+=CELL_SIZE)
    {
        draw_line(i, 0, i, size.y);
    }
    //drawing y lines
    for(int i = 0; i<size.y; i +=CELL_SIZE)
    {
        draw_line(0, i, size.x, i);
    }
}

void draw_cell(float x, float y)
{
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(CELL_SIZE-1, CELL_SIZE-1));
    rect.setFillColor(sf::Color::Cyan);
    rect.setPosition(x, y);
    window.draw(rect);
}

void draw_cell(int cell_id)
{
    int yk = (int)(cell_id/20);
    int xk = (int)(cell_id-yk*20);
    //std::cout<<"DRAW CELL:"<<xk<<" "<<yk<<std::endl;
    //add cell to memory
    cells[xk][yk] = true;
    draw_cell(xk*CELL_SIZE, yk*CELL_SIZE);
}

void onmouse()
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    int xk = (int)mouse_pos.x/CELL_SIZE;
    int yk = (int)mouse_pos.y/CELL_SIZE;
    draw_cell(xk+yk*20);
    //std::cout<<xk<<" "<<yk<<" "<<xk+yk*20<<std::endl;

}

void main_game()
{
    draw_grid();
    //If not pause
    if(!PAUSE)
    {
        //Without border cells
        for(int i = 0;i<20;i++)
        {
            for(int j = 0;j<20;j++)
            {
                //Magick. Rework!!!
                int alive_count = 0;
                if(i != 0 && i != 20 && j != 0 && j != 20)
                {
                    if(cells[i][j+1])
                        alive_count++;

                    if(cells[i+1][j])
                        alive_count++;

                    if(cells[i+1][j+1])
                        alive_count++;

                    if(cells[i][j-1])
                        alive_count++;

                    if(cells[i-1][j])
                        alive_count++;

                    if(cells[i-1][j-1])
                        alive_count++;

                    if(cells[i-1][j+1])
                        alive_count++;

                    if(cells[i+1][j-1])
                        alive_count++;
                }
                if(i == 0 || j == 0)
                {
                    if(cells[i][j+1])
                        alive_count++;

                    if(cells[i+1][j+1])
                        alive_count++;

                    if(cells[i+1][j])
                        alive_count++;
                }
                if(i == 20 || j == 20)
                {
                    if(cells[i][j-1])
                        alive_count++;

                    if(cells[i-1][j-1])
                        alive_count++;

                    if(cells[i-1][j])
                        alive_count++;
                }
                //Calculating alive and dead cells
                if(!cells[i][j] && alive_count==3)
                    cells[i][j] = true;
                if(cells[i][j] && (alive_count<2 || alive_count>3))
                    cells[i][j] = false;

            }
        }
    }
    //Draw cells from memory
    for(int i = 0;i<20;i++)
    {
        for(int j = 0;j<20;j++)
        {
            if(cells[i][j])
            {
                draw_cell(i*CELL_SIZE, j*CELL_SIZE);
            }
        }
    }
}

int main()
{

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                PAUSE = !PAUSE;
            }
            if(event.MouseLeft && PAUSE)
            {
                onmouse();
            }
            if(event.type == sf::Event::Closed)
                window.close();

        }
        //Main loop
        main_game();
        window.display();
        window.clear();
    }


    return 0;
}
