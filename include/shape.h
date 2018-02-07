#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <iostream>
#include <vector>
#include "brick.h"

using namespace std;

class Shape {
    // don't consider collision
    // detect collision in ground
protected:
    vec3 color;
    vector<Brick> bricks;
    Brick *pivot;

public:
    Shape() {}
    Shape(vec3 color): color(color) {}

    bool hasBrick(vec2 position) {
        for(auto& brick: bricks) {
            if(brick.getPosition() == position){
                return true;
            }
        }
        return false;
    }

    void setAllBricks(vector<vec2> new_positions) {
        // assume the size of two vectors are the same
        for(unsigned i = 0; i < bricks.size(); i++) {
            bricks[i].setPosition(new_positions[i]);
        }
    }

    vector<vec2> getBrickPositions() {
        vector<vec2> positions;
        for(auto& brick: bricks) {
            positions.push_back(brick.getPosition());
        }
        return positions;
    }

    void setColor(vec3 new_color) {
        color = new_color;
    }

    vec3 getColor() {
        return color;
    }

    vector<vec2> getNewPositionsRotation() {
        // show the new occupied positions 
        vector<vec2> new_positions;
        vec2 pivot_position = pivot->getPosition();
        vec2 brick_position;
        for(auto& brick: bricks) {
            brick_position = brick.getPosition();
            // apply rotatation formula
            vec2 new_position = vec2(
                    pivot_position[0] + pivot_position[1] - brick_position[1],
                    -pivot_position[0] + pivot_position[1] + brick_position[0]
                );
            new_positions.push_back(new_position);
        }
        return new_positions;
    }

    // TODO: how to deal with the strange floating number when the result is 0?
    void rotate() {
        // not use rotation matrix to rotate.
        // since only rotate 90 degree, write the code directly
        vector<vec2> new_positions = getNewPositionsRotation();
        setAllBricks(new_positions);
    }

    vector<vec2> getNewPositionsMove(char direction) {
        vector<vec2> new_positions;
        vec2 translation_vec;
        switch(direction) {
            case 'u':
                translation_vec = vec2(0, 1);
                break;
            case 'd':
                translation_vec = vec2(0, -1);
                break;
            case 'l':
                translation_vec = vec2(-1, 0);
                break;
            case 'r':
                translation_vec = vec2(1, 0);
                break;
        }
        for(auto& brick: bricks) {
            vec2 new_position = vec2(brick.getPosition()+translation_vec);
            // add to new positions list
            new_positions.push_back(new_position);
        }
        return new_positions;
    }

    void move(char direction) {
        vector<vec2> new_positions = this->getNewPositionsMove(direction);
        setAllBricks(new_positions);
    }

    void print() {
        // for test purpose
        cout << "position of brick:" << endl;
        for(auto& brick: bricks) {
            cout << "\t" << brick.getPosition() << endl;
        }
        cout << "color : " << color << endl;
    }

};

class TShape: public Shape {
public:
    TShape(vec2 pivot_position, vec3 color): Shape(color) {
        bricks.emplace_back(pivot_position, color);
        bricks.emplace_back(pivot_position + vec2(-1, 0), color);
        bricks.emplace_back(pivot_position + vec2(1, 0), color);
        bricks.emplace_back(pivot_position + vec2(0, -1), color);
        pivot = &bricks[0];
    }
};

class JShape: public Shape {
public:
    JShape(vec2 pivot_position, vec3 color): Shape(color) {
        bricks.emplace_back(pivot_position, color);
        bricks.emplace_back(pivot_position + vec2(-1, 0), color);
        bricks.emplace_back(pivot_position + vec2(1, 0), color);
        bricks.emplace_back(pivot_position + vec2(1, -1), color);
        pivot = &bricks[0];
    }
};

class LShape: public Shape {
public:
    LShape(vec2 pivot_position, vec3 color): Shape(color) {
        bricks.emplace_back(pivot_position, color);
        bricks.emplace_back(pivot_position + vec2(-1, 0), color);
        bricks.emplace_back(pivot_position + vec2(1, 0), color);
        bricks.emplace_back(pivot_position + vec2(-1, -1), color);
        pivot = &bricks[0];
    }
};

class ZShape: public Shape {
public:
    ZShape(vec2 pivot_position, vec3 color): Shape(color) {
        bricks.emplace_back(pivot_position, color);
        bricks.emplace_back(pivot_position + vec2(-1, 0), color);
        bricks.emplace_back(pivot_position + vec2(1, -1), color);
        bricks.emplace_back(pivot_position + vec2(0, -1), color);
        pivot = &bricks[0];
    }
};

class IShape: public Shape {
public:
    IShape(vec2 pivot_position, vec3 color): Shape(color) {
        bricks.emplace_back(pivot_position, color);
        bricks.emplace_back(pivot_position + vec2(-2, 0), color);
        bricks.emplace_back(pivot_position + vec2(-1, 0), color);
        bricks.emplace_back(pivot_position + vec2(1, 0), color);
        pivot = &bricks[0];
    }
};

class OShape: public Shape {
public:
    OShape(vec2 pivot_position, vec3 color): Shape(color) {
        bricks.emplace_back(pivot_position, color);
        bricks.emplace_back(pivot_position + vec2(-1, 0), color);
        bricks.emplace_back(pivot_position + vec2(-1, -1), color);
        bricks.emplace_back(pivot_position + vec2(0, -1), color);
        pivot = &bricks[0];
    }
};

// create a random shape
template<typename T>
Shape *Create(vec2 pivot_position, vec3 color) {
    return new T(pivot_position, color);
}

typedef Shape* (*CreateFn)(vec2, vec3);
CreateFn createArray[] = {
    &Create<TShape>,
    &Create<OShape>,
    &Create<IShape>,
    &Create<ZShape>,
    &Create<LShape>,
    &Create<JShape>,
};

const size_t fncount = sizeof(createArray)/sizeof(*createArray);
Shape *Create(vec2 pivot_position, vec3 color) {
   return createArray[rand() % fncount](pivot_position, color); //forward the call
}


#endif