#include "../include/tui.hpp"
#include <ftxui/screen/screen.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>

using namespace ftxui ;
using namespace std ;

void runTUI(const string &repoName, const vector<FileStat> &stats) {

    int selected = 0;
    
    auto screen = ScreenInteractive::Fullscreen();
    
    auto renderer = Renderer([&] {
        
        Elements items;
          items.push_back(text(repoName) | bold | center);
          items.push_back(separator());
          float maxTouches = stats[0].touchCount; 
          
          for(int i = 0; i < 20 && i < (int)stats.size(); i++) {
              
              float ratio = stats[i].touchCount / maxTouches;
              items.push_back(hbox({
                  text(stats[i].fileName) | size(WIDTH, EQUAL, 30),
                  gauge(ratio) | size(WIDTH, EQUAL, 40) | color(Color::Blue),
                  text(" " + to_string(stats[i].touchCount))
              }));
              items.push_back(text(""));
          }

          
          return vbox(items);
    });

    auto component = renderer | CatchEvent([&](Event event) -> bool {
        
        if(event == Event::Character('q')) {
            screen.ExitLoopClosure()();
            return true ; 
        }
        return false ;
    });
  
    
    screen.Loop(component);
}