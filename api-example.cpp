
// main

int main()
{
    NewGame game();
    game.Start();
    
}


// in NewGame file
class NewGame : public Game
{

public:

    NewGame()
    {
        m_Spritebatch = SpriteBatch(some args)
        
    }

    void Load()
    {
        m_PlayerTexture = Content.Load<Texture2D>("Player");
    }
    void Update(Time time);
    void Render(Time time);

private:

    SpriteBatch m_Spritebatch;
    Texture2D m_PlayerTexture;
    int n_someInt;

}

class Spritebatch
{
    
}

