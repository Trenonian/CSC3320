import java.util.Scanner;

class class foo {
  public static void main(String[] args) {
    int x = 0;
    int i = 1;
    System.out.println("please enter a number");
    Scanner console = new Scanner(System.in);
    int num = console.nextInt();
    console.close();
    while (i <= num) {
      int s = i * i;
      x = s + x;
      i = i + 1;
    }
    System.out.println(x);
  }
}