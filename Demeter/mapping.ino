void map_x()
{
  vx = analogRead(Vrx);
  vx = map(vx, 32, 1020, 0, 100);
  if ((vx >= 45) && (vx <= 55))
  {
    vx = 0;
  }
  else if (vx < 47)
  {
    vx = -1;
  }
  else if (vx > 55)
  {
    vx = 1;
  }
}

void map_y()
{
  vy = analogRead(Vry);
  vy = map(vy, 32, 1020, 0, 100);
  if ((vy >= 45) && (vy <= 55))
  {
    vy = 0;
  }
  else if (vy < 45)
  {
    vy = 1;
  }
  else if (vy > 55)
  {
    vy = -1;
  }
}
