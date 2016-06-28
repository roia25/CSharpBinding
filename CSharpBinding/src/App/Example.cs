using System;

class Hello
{
  static void Main()
  {
    Console.WriteLine("Hello World!");
  }
}

namespace Example
{
  public class Entity
  {
    private int Id;
    private string name;

    public Entity(string name)
    {
      this.name = name;
      this.Id = 0;
      Console.WriteLine("Entity " + name + " constructed");
    }

    ~Entity()
    {
      Console.WriteLine("Entity " + name + " destructed");
    }

    public void Process()
    {
      throw new NotImplementedException("Not implemented yet");
    }
    public string GetName()
    {
      return name;
    }

    public int GetId()
    {
      return Id;
    }
  }
}
