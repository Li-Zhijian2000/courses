import TokenType.TokenType

class Lexer() {
  def parse(in: LazyList[Char]): LazyList[TokenType] = in.headOption.map {
    case ch if isSpace(ch) => parse(in.dropWhile(isSpace(_)))
    case ch if ch.isDigit => lexInt(in)
    case ch if ch.isLetter => lexIdentAndKeyword(in)
    case ch if isOperator(ch) => lexOperator(in)
    case _ => TokenType.Unknown #:: LazyList.empty
  }.getOrElse(LazyList.empty)

  private def isSpace = " \t\r\n".toCharArray.contains(_)

  private def isOperator = ":+*,()".toCharArray.contains(_)

  private def toString(in: LazyList[Char]) = String.valueOf(in.toArray)

  def lexInt(in: LazyList[Char]): LazyList[TokenType] = {
    val (res, rem) = in.span(_.isDigit)
    TokenType.Integer(toString(res).toInt) #:: parse(rem)
  }

  def lexIdentAndKeyword(in: LazyList[Char]): LazyList[TokenType] = {
    val (res, rem) = in.span(_.isLetterOrDigit)
    val token = toString(res) match {
      case "BEGIN" => TokenType.Begin
      case "END" => TokenType.End
      case "FOR" => TokenType.For
      case "IF" => TokenType.If
      case "THEN" => TokenType.Then
      case "ELSE" => TokenType.Else
      case ident => TokenType.Ident(ident)
    }
    token #:: parse(rem)
  }

  def lexOperator(in: LazyList[Char]): LazyList[TokenType] = {
    in match {
      case ':' #:: '=' #:: rem => TokenType.Assign #:: parse(rem)
      case op #:: rem =>
        val token = op match {
          case ':' => TokenType.Colon
          case '+' => TokenType.Plus
          case '*' => TokenType.Star
          case ',' => TokenType.Comma
          case '(' => TokenType.LParenthesis
          case ')' => TokenType.RParenthesis
        }
        token #:: parse(rem)
    }
  }
}
