class Shape {
    String name;
    int width, length;
    Shape(String newName) {
        name = newName;
    }
    void print() {
        System.out.println(name + "(" + width +", " + length + ") : " + Double.toString(area()));
    }

    void draw() {
        System.out.print("this should never happen");
    }

    double area() {
        return 0.0;
    }
}

class Circle extends Shape {
    private int radius = 0;

    private static final double pi = 3.14159265359;
    
    public Circle(String newName, int newRadius) {
        super(newName);
        radius = newRadius;
    }

    void draw() {
        double threshold = 0.5;

        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                double distance = Math.sqrt(i * i + j * j);

                if (distance > radius - threshold && distance < radius + threshold)
                    System.out.print("*");
                else
                    System.out.print(" ");
            }
            System.out.println();
        }
    }

    void print() {
        System.out.println(name + "(" + radius + ") : " + String.format( "%.2f", area()));
    }

    double area() {
        return pi * radius * radius;
    }
}

class Square extends Shape {
    private int side;
    Square(String newName, int newSide) {
        super(newName);
        side = newSide;
    }

    void draw() {
        int size = 5;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i == 0 || i == size - 1 || j == 0 || j == size - 1) {
                    System.out.print("*");
                } else {
                    System.out.print(" ");
                }
            }
            System.out.println();
        }
    }

    void print() {
        System.out.println(name + "(" + side + ") : " + Double.toString(area()) );
    }

    double area() {
        return side * side;
    }

}

class Triangle extends Shape {
    int base, height;
    Triangle(String newName, int newBase, int newHeight){
        super(newName);
        base = newBase;
        height = newHeight;
    }

    void draw() {

        for (int i = 1; i <= height; i++) {
            for (int j = i; j < height; j++) {
                System.out.print(" ");
            }

            for (int j = 1; j < 2 * i; j++) {
                if (j > 1 && j < (2 * i - 1)) {
                    System.out.print(" ");
                } else {
                    System.out.print("*");
                }
            }

            System.out.println();
        }
    }

    void print() {
        System.out.println(name + "(" + base + ", " + height + ") : " + Double.toString(area()) );
    }

    double area() {
        return (double) (base * height) / 2;
    }
}

class Rectangle extends Square {
    int base, height;
    Rectangle(String newName, int newBase, int newHeight) {
        super(newName, newBase);
        base = newBase;
        height = newHeight;
    }

    void print() {
        System.out.println(name + "(" + base + ", " + height + ") : " + Double.toString(area()) );
    }

    double area() {
        return base * height;
    }
}

// Example Activity of linked list


class Picture{
    static class ListNode {
        Shape info;
        ListNode next;
        ListNode(Shape info, ListNode next) {
            this.info = info;
            this.next = next;
        }
    }
    ListNode head;
    Picture() {
        head = null;
    }
    void add(Shape sh){
        if (head == null) {
            head = new ListNode(sh, null);
        } else {
            ListNode temp = head;
            for (; temp.next != null; temp = temp.next) {
            }
            temp.next = new ListNode(sh, null);
        }
    }

    void printAll() {
        for (ListNode p = head; p!=null; p=p.next) {
            p.info.print();
        }
    }

    void drawAll() {
        for (ListNode p = head; p!=null; p=p.next) {
            p.info.draw();
        }
    }

    double totalArea() {
        double totalArea = 0;
        for (ListNode p = head; p!=null; p=p.next) {
            totalArea = totalArea + p.info.area();
        }
        return totalArea;
    }
}

public class mainClass {
    public static void main(String[] args) {
        int x;
        int y;

        x = Integer.parseInt(args[0]);
        y = Integer.parseInt(args[1]);

        Picture picture = new Picture();
        picture.add(new Triangle("FirstTriangle", x, y));
        picture.add(new Triangle("SecondTriangle", x - 1, y - 1));
        picture.add(new Circle("FirstCircle", x));
        picture.add(new Circle("SecondCircle", x - 1));
        picture.add(new Square("FirstSquare", x));
        picture.add(new Square("SecondSquare", x - 1));
        picture.add(new Rectangle("FirstRectangle", x, y));
        picture.add(new Rectangle("SecondRectangle", x-1, y-1));
        picture.printAll();
        picture.drawAll();
        System.out.printf("Total: %.2f\n", picture.totalArea());
    }
}