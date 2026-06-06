#include "../include/tui.hpp"
#include "utils.hpp"
#include <ftxui/screen/screen.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>

using namespace ftxui ;
using namespace std ;

void runTUI(const string &repoName, const vector<FileStat> &stats , const vector<Chapter> &chapters) {

    int selected = 0;

    bool showChapters = false ; 
    
    auto screen = ScreenInteractive::Fullscreen();
    
    auto renderer = Renderer([&] {
        
        Elements items;
          items.push_back(text(repoName) | bold | center);
          items.push_back(separator());
       

          if(showChapters) {
              for (int i = selected; i < selected + 20 && i < (int)chapters.size(); i++) {
                       items.push_back(hbox({
                           text(formatDate(chapters[i].startDate) + " -> " + formatDate(chapters[i].endDate)) | size(WIDTH, EQUAL, 25),
                           text(chapters[i].name) | size(WIDTH, EQUAL, 25),
                           text(to_string(chapters[i].commitCount))
                       }));
              }
          }
          else {
                 float maxTouches = stats[0].touchCount; 
                 for(int i = selected; i < selected + 20 && i < (int)stats.size(); i++) {
                     
                     float ratio = stats[i].touchCount / maxTouches;
                     
                     items.push_back(hbox({
                         text(stats[i].fileName) | size(WIDTH, EQUAL, 30),
                         gauge(ratio) | size(WIDTH, EQUAL, 40) | color(Color::Blue),
                         text(" " + to_string(stats[i].touchCount))
                     }));
                     
                     items.push_back(text(""));
                 }
          }
          
      

          
          return vbox(items);
    });

    auto component = renderer | CatchEvent([&](Event event) -> bool {
        
        if(event == Event::Character('q')) {
            screen.ExitLoopClosure()();
            return true ; 
        }

        if(event == Event::ArrowDown) {
            if(selected + 20 < (int)stats.size()) selected++;
            return true ; 
        }

        if(event == Event::ArrowUp) {
            if(selected > 0) selected--;
            return true ; 
        }

        if(event == Event::Character('c')) {
            showChapters  = !showChapters ;
            selected = 0 ;
            return true ; 
        }
        
        return false ;
    });
  
    
    screen.Loop(component);
}