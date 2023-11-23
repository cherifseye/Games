 #include <SFML/Graphics.hpp>
#include <vector>
#include <array>

using namespace sf;

const float spacer = 5.0f;
float heightLines = 0.0f;
std::vector<std::array<Vertex, 2>> Rows;
std::vector<std::array<Vertex, 2>> Cols;
std::vector<std::vector<int>> grid;

int main(){
    VideoMode vm (500, 500);
    RenderWindow window(vm, "Cases", Style::Default);
    const int nRows = static_cast<int>(window.getSize().x / spacer);
    const int nCols = static_cast<int>(window.getSize().y / spacer);
    
    grid.resize(nRows, std::vector<int>(nCols, 0));
    grid[1][0] = 1;
    grid[2][1] = 1;
    grid[0][2] = 1;
    grid[1][2] = 1;
    grid[2][2] = 1;
    
    for (int i=0; i<nRows; i++){
        std::array<Vertex, 2> line = {
            Vertex(Vector2f(0, heightLines)),
            Vertex(Vector2f(window.getSize().x, heightLines))
       };
       Rows.push_back(line);
       heightLines += spacer;
    }
    heightLines = 0.0f;
    for (int i=0; i<nCols; i++){
        std::array<Vertex, 2> line = {
            Vertex(Vector2f(heightLines, 0)),
            Vertex(Vector2f(heightLines, window.getSize().y))
       };
       Cols.push_back(line);
       heightLines += spacer;
    }
    
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();
            }
        }
        window.clear();
        for(auto& line : Rows) {
            window.draw(line.data(), 2, Lines);
        }
        for(auto& line : Cols) {
            window.draw(line.data(), 2, Lines);
        }
        
        std::vector<std::vector<int>> newGrid = grid;
    
        // Game of Life rules
        for (int i = 0; i < nRows; ++i) {
            for (int j = 0; j < nCols; ++j) {
                int liveNeighbors = 0;
                for (int x = -1; x <= 1; ++x) {
                    for (int y = -1; y <= 1; ++y) {
                        if (x == 0 && y == 0)
                            continue;
                        int ni = i + x;
                        int nj = j + y;
                        if (ni >= 0 && ni < nRows && nj >= 0 && nj < nCols && grid[ni][nj] == 1)
                            ++liveNeighbors;
                    }
                }
                if (grid[i][j] == 1 && (liveNeighbors < 2 || liveNeighbors > 3))
                    newGrid[i][j] = 0;
                else if (grid[i][j] == 0 && liveNeighbors == 3)
                    newGrid[i][j] = 1;
                
                if (newGrid[i][j] == 1) {
                    RectangleShape cell;
                    cell.setSize(Vector2f(spacer, spacer));
                    cell.setPosition(Vector2f(i * spacer, j * spacer));
                    window.draw(cell);
                    sleep(milliseconds(20));
                }
            }
        }
        
        grid = newGrid;
        
        window.display();
    }
}