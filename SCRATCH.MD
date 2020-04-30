
# Mermaid RPG

RPG Session Manager. Programmer Style.

## Tasks

- [X] Managed Font, Renderer and Window
- [-] Application
- [.] Event system
    - [X] Mouse Enter
    - [X] Mouse Leave
    - [X] Mouse Move
    - [X] Click
    - [ ] Drag Start
    - [ ] Drag Move
    - [ ] Drag End
    - [ ] Key Down
    - [ ] Key Up
    - [ ] TextInput
    - [ ] Improve Event Info (e.g.: event local position)
    - [ ] Window Enter
    - [ ] Window Leave
    - [ ] Window Move
    - [ ] Window Re size
    - [ ] Focus in
    - [ ] Focus out
- [.] Widget System
    - [X] View
    - [X] Label
    - [X] HBox
    - [X] VBox
    - [ ] Button
        - [ ] Implementation
        - [ ] Make it work when mouse leaves and comes back with button down
        - [ ] WindowLeave return it to its default state
    - [ ] Image
    - [ ] TextInput
    - [ ] Checkbox
    - [ ] SelectBox
    - [ ] Radio
    - [ ] Add scintilla like code editor (https://www.scintilla.org/index.html)
- [ ] ViewModel System (vue/react like with view files and code generation)
- [ ] Box Model(Border, padding, margin)
- [ ] View

## Sample ViewModel File

https://github.com/khlam/CS480-Translators/tree/master/3
```
#comments
//comments
/*
Comments
*/
namespace fulano::beltrano; //optional namespace
class Teste; //optional classname

Name {
    data {
        int var = value;
        float other = otherValue;
        bool var = value;
        string teste = "123";
        string teste2 = '123';
        char teste = 123;
        unsigned teste; // no default value
    }
    props {
        int a;
        int b;
        int c;
    }
    init {
        
    }
    layout {
        <View @click="clickMethod" :enabled="state.var == 0" ref="view">
            <Child ref="child ${data.var}">
                <Label text="Fazer ok ${data.teste}" @hover="changeData"/>
            </Child>
        </View>
    }
}
```

## References & Utilities
- Maybe rename to siren
- SFGUI: https://github.com/TankOs/SFGUI/tree/master/src/SFGUI
- http://utfcpp.sourceforge.net/
- https://kivy.org/#home
- GUI Style: https://odiogosilva.github.io/TriFusion/
