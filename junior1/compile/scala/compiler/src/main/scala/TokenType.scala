object TokenType extends Enumeration {
  type TokenType = Value
  val Begin, End, For, If, Then, Else,
  Colon, Plus, Star, Comma, LParenthesis, RParenthesis, Assign, Unknown, EOF = Value

  case class Ident(name: String) extends TokenType.Value {
    override def id: Int = -1

    override def toString: String = s"Ident($name)"
  }

  case class Integer(value: Int) extends TokenType.Value {
    override def id: Int = -2

    override def toString: String = s"Int($value)"
  }

}