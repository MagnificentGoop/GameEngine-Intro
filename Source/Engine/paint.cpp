#include "Paint.h"
#include "Random.h"
namespace bad {
    paint::paint() {
        points = new std::vector<std::vector<bad::Vector2<float>*>*>();
    }

    void paint::Update(bad::Input& input) {
        if (input.GetButtonDown(bad::Input::LEFT)) {
            points->push_back(new std::vector<bad::Vector2<float>*>());
            points->back()->push_back(new bad::Vector2(input.GetMousePosition()));
        }
        else if (input.GetButtonPressed(bad::Input::LEFT)) {
            if (points->size() != 0 && points->back()->size() != 0) {
                bad::Vector2<float> temp = input.GetMousePosition();
                if (temp.LengthBtwn(points->back()->back()) > 10.0f) {
                    points->back()->push_back(new bad::Vector2(input.GetMousePosition()));
                }
            }
        }

        if (input.GetButtonDown(bad::Input::MIDDLE)) {
            for (int i = points->size() - 1; i > -1; i--)
            {
                for (int j = points->at(i)->size() - 1; j > -1; j--)
                {
                    delete points->at(i)->at(j);
                }
                delete points->at(i);
            }
            delete points;
                points = new std::vector<std::vector<bad::Vector2<float>*>*>();
        }

        if (input.GetButtonDown(bad::Input::RIGHT)) {
            if (points->size() != 0) {
                if (points->back()->size() != 0) {
                    for (int i = points->back()->size() - 1; i > -1; i--)
                    {
                        delete points->back()->at(i);
                    }
                }
                delete points->back();
                points->pop_back();
            }
        }
    }

    void paint::Render(bad::Renderer& rend) {
        for (int i = 0; i < points->size(); i++)
        {
            for (int j = 1; j < points->at(i)->size(); j++)
            {
                rend.SetColor(bad::RandomInt(255), bad::RandomInt(255), bad::RandomInt(255));
                rend.DrawLine(points->at(i)->at((j - 1)), points->at(i)->at(j), Color8(255,255,255));
            }
        }
    }
}