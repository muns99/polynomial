#include "polynomial.h"

Polynomial::Polynomial(Node* h) : head(h)
{
    if(h==NULL)
        numofterms =0;
    else numofterms = 1;
}

Polynomial::Polynomial(const Polynomial& p)
{
    Node* current = p.head;
    Node* attach ;
    if(current)
    {
        head = new Node;
        head->next = NULL;
        head->coef = current->coef;
        head->exp = current->exp;
    }
    attach = head;
    current = current->next;
    while(current)
    {
        Node* newcar = new Node;
        newcar->coef = current->coef;
        newcar->exp = current->exp;
        newcar->next = attach->next;
        attach->next = newcar;
        attach = attach->next;
        current = current->next;
    }

}

Polynomial::~Polynomial()
{
    Node* current = head;
    Node* old ;
    while(current){
        old = current;
        current = current->next;
        delete old;

    }
}

void Polynomial::print() const
{
    Node* current = head;
    while(current)
    {
        cout<<current->coef<<"X^"<<current->exp<<" ";
        current=current->next;
    }
}

void Polynomial::add_term(const double& c, const int& e)
{
    numofterms++;
    // Empty linked list
    if(head == NULL)
    {
        head = new Node;
        head->coef = c;
        head->exp = e;
        head->next = NULL;
        return;
    }
    // Single term
    if(head->next == NULL)
    {
        Node* newcar = new Node;
        newcar->coef = c;
        newcar->exp = e;
        if(head->exp > newcar->exp)
        {
            newcar->next = NULL;
            head->next = newcar;
        }
        else if (head->exp < newcar->exp)
        {
            newcar->next = head;
            head = newcar;

        }
        else
        {
            delete newcar;
            head->coef += c;
            if (head->coef == 0)

            {
                remove_term(head->exp);
            }
            return;

        }


    }
    // Multiple terms
    else
    {
        Node* current = head;
        while(current)
        {
            // Last term in list
            if(current->exp ==e )
                {
                    current->coef += c;
                    if(current->coef == 0)
                        remove_term(current->exp);
                    return;
                }
            if( current->next == NULL)
            {
                Node* newcar = new Node;
                newcar->coef = c;
                newcar->exp = e;
                newcar->next = NULL;
                current->next = newcar;
                return;
            }


            // Add between two terms
            else if(e<current->exp  && e>current->next->exp)
            {
                Node* newcar = new Node;
                newcar->coef = c;
                newcar->exp = e;
                newcar->next = current->next;
                current->next = newcar;
                return;
            }
            // Update
            current = current->next;
        }
    }

}

Polynomial Polynomial::p_copy() const
{
    Polynomial res(*this);
    return res;
}

void Polynomial::remove_term(const int& e)
{
    if(head->exp == e)

    {
        Node* old = head;
        head = head->next;
        delete old;
        return;
    }

    else
    {
        Node* current = head;
        while(current->next)
        {
            if(current->next->exp == e)
            {
                Node* old = current->next;
                current->next = current->next->next;
                delete old;
                return;
            }
            current=current->next;
        }

    }
}

double Polynomial::poly_val(const double& x) const
{
    Node* current = head ;
    double res = 0;
    while(current)
    {
        res+= (current->coef * pow(x,current->exp));
        current = current->next;
    }
    return res;

}

Polynomial Polynomial::mul_term(const double& c, const int& e) const
{

    Polynomial res(*this);
    Node* current = res.head;;
    while(current)
    {
        current->coef *= c;
        current->exp += e;
        current=current->next;
    }
    return res;

}

bool Polynomial::operator==(const Polynomial& p) const
{
    Node* current = head;
    Polynomial pp = p;
    Node* com = pp.head;
    while(current && com)
    {
        if(current->coef != com->coef || current->exp != com->exp )
            return false;
        current = current->next;
        com = com->next;
    }
    if(current || com)
        return false;

    return true;
}

bool Polynomial::operator!=(const Polynomial& p) const
{
    if(p.numofterms != numofterms) return true;
    Node* current = head;
    Polynomial pp = p;
    Node* com = pp.head;
    while(current && com)
    {
        if(current->coef == com->coef || current->exp == com->exp )
            return false;
        current = current->next;
        com = com->next;
    }
    /*if(current || com)
        return true;*/

    return true;
}

Polynomial Polynomial::operator + (const Polynomial& p) const
{
    Polynomial res(*this);
    Node* current = p.head;
    while(current)
    {
        res.add_term(current->coef,current->exp);
        current=current->next;
    }
    return res;

}

Polynomial Polynomial::operator - (const Polynomial& p) const
{
    Polynomial res(*this);
    Node* current = p.head;
    while(current)
    {
        res.add_term(-current->coef,current->exp);
        current=current->next;
    }
    return res;
}

Polynomial Polynomial::operator * (const Polynomial& p) const // complexity
{
    Polynomial res(*this);
    Node* current = p.head;
    Polynomial mult;

    while(current)
    {
        mult = res.mul_term(current->coef,current->exp);
        res = res + mult;
        current = current->next;
    }
    return res;
}

Polynomial Polynomial::operator / (const Polynomial& divisor) const
{}

Polynomial Polynomial::operator % (const Polynomial& divisor) const
{}

Polynomial Polynomial::differentiate () const
{
    Polynomial res(*this);
    Node* current = res.head;
    while(current)
    {
        if(current->exp == 0)
        {res.remove_term(current->exp); continue;}
        current->coef *= current->exp;
        current->exp-=1;
        current = current->next;

    }
    return res;
}

Polynomial Polynomial::integrate () const
{
    Polynomial res(*this);
    Node* current = res.head;
    while(current)
    {
        current->coef /= current->exp;
        current->exp+=1;
        current = current->next;

    }
    return res;
}

