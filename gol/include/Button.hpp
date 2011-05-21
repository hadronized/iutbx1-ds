#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Text.hpp"

/**
 * @class ButtonBase
 * @brief Widget de base pour les boutons
 *
 * Ce widget permet de gerer des boutons en tout genre. Il permet notamment d'apposer du texte sur un bouton.
 */
class ButtonBase : public WidgetBase {
protected :
    Text _text;

    /**
     * @fn void maj(void)
     * @brief Met a jour les donnees SFML du bouton
     */
    void maj(void);

public :
    /**
     * @fn ButtonBase(Frame frame, sf::Sprite sprite, std::string const &text = "")
     * @brief Constructeur paramétré surchargé
     * @param text optionnel, le texte a afficher sur le bouton (centre)
     */
    ButtonBase(Frame frame, sf::Sprite sprite, std::string const &text = "");
    /**
     * @fn ~ButtonBase(void)
     * @brief Destructeur
     */
    virtual ~ButtonBase(void);

    void draw(sf::RenderWindow &window) const;
};


/**
 * @class PushButton
 * @brief Widget bouton-poussoir
 *
 * Ce widget est un bouton poussoir. Il emet une notification capturable lorsque l'utilisateur appuit dessus.
 */
class PushButton : public ButtonBase {
public :
    /**
     * @class Listener
     * @brief Listener sur PushButton
     */
    class Listener {
    public :
        /**
         * @fn Listener(void)
         * @brief Constructeur par defaut
         */
        Listener(void);
        /**
         * @fn ~Listener(void)
         * @brief Destructeur
         */
        ~Listener(void);

        /**
         * @fn void notifyUp(PushButton &send);
         * brief Notification de clic sur le bouton
         *
         * Cette fonction doit etre redefinie dans les Listener filles.
         */
        virtual void notifyUp(PushButton &send) = 0;
    };

protected :
    Listener *_pListener;

public :
    /**
     * @fn PushButton(Frame frame, sf::Sprite sprite, Listener *pListener = 0)
     * @brief Constructeur parametre surcharge
     * @param pListener optionnel, permet de lier le bouton a une action
     */
    PushButton(Frame frame, sf::Sprite sprite, Listener *pListener = 0);
    /**
     * @fn ~PushButton(void)
     * @brief Destructeur
     */
    ~PushButton(void);

    /**
     * @fn void reset(void)
     * @brief Reinitialise le bouton
     *
     * Dans le cas d'un PushButton, cette methode permet tout simplement de ramener le bouton a l'etat unchecked.
     */
    void reset(void);
    bool relayEvents(sf::Event const &event, sf::Input const &input);
    /**
     * @fn void setListener(Listener *pListener)
     * @brief Permet d'attacher un listener au bouton
     * @param pListener listener a attache (assertion sur la validite du pointeur)
     */
    void setListener(Listener *pListener);
};


/**
 * @class ToggleButton
 * @brief Widget bouton
 */
class ToggleButton : public ButtonBase {
public :
    class Listener {
    public :
        Listener(void);
        ~Listener(void);
      ButtonBase & add(ButtonBase *Button);

        virtual void notifyToggle(ToggleButton &sender) = 0;
    };

protected :
    sf::Sprite _sprite2;
    bool _checked;
    bool _forced;
    Listener *_pListener;
  
    void changeAppearance(void); // change l'apparance du bouton en fonction de son état

public :
    ToggleButton(Frame frame, sf::Sprite sprite, sf::Sprite sprite2,
		 Listener *pListener = 0, bool checked = false,
		 bool forced = false, std::string const &text = "");
    ~ToggleButton(void);

    void maj(void);

    /**
     * @fn void reset(void)
     * @brief Reinitialise le bouton
     *
     * Dans le cas d'un PushButton, cette methode permet tout simplement de ramener le bouton a l'etat unchecked.
     */
    void reset(void);
    void draw(sf::RenderWindow &window) const;
    bool relayEvents(sf::Event const &event, sf::Input const &input);
    bool is_checked(void) const;
    bool is_forced(void) const;
};

#endif
