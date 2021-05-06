char *somestr(void)
{
  static char text[] = "Hello world";
  return text;
}

// static char *text = "Hello, world!"