SET SERVEROUTPUT ON;

CREATE OR REPLACE FUNCTION is_armstrong(n NUMBER)
RETURN VARCHAR2
IS
    temp NUMBER := n;
    rem NUMBER;
    arm_sum NUMBER := 0;
    digits NUMBER := 0;
BEGIN
    WHILE temp > 0 LOOP
        digits := digits + 1;
        temp := FLOOR(temp / 10);
    END LOOP;

    temp := n;

    WHILE temp > 0 LOOP
        rem := MOD(temp, 10);
        arm_sum := arm_sum + POWER(rem, digits);
        temp := FLOOR(temp / 10);
    END LOOP;

    IF arm_sum = n THEN
        RETURN n || ' is an ARMSTRONG number.';
    ELSE
        RETURN n || ' is NOT an ARMSTRONG number.';
    END IF;
END;
/
BEGIN
    DBMS_OUTPUT.PUT_LINE(is_armstrong(&n));
END;



SET SERVEROUTPUT ON;

CREATE OR REPLACE PROCEDURE check_armstrong(n NUMBER)
IS
    temp NUMBER := n;
    rem NUMBER;
    arm_sum NUMBER := 0;
    digits NUMBER := 0;
BEGIN
    WHILE temp > 0 LOOP
        digits := digits + 1;
        temp := FLOOR(temp / 10);
    END LOOP;

    temp := n;

    WHILE temp > 0 LOOP
        rem := MOD(temp, 10);
        arm_sum := arm_sum + POWER(rem, digits);
        temp := FLOOR(temp / 10);
    END LOOP;

    IF arm_sum = n THEN
        DBMS_OUTPUT.PUT_LINE(n || ' is an ARMSTRONG number.');
    ELSE
        DBMS_OUTPUT.PUT_LINE(n || ' is NOT an ARMSTRONG number.');
    END IF;
END;
/
BEGIN
    check_armstrong(&n);
END;
