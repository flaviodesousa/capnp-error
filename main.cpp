#include <fcntl.h>
#include <unistd.h>

#include "addressbook.capnp.h"
#include <capnp/message.h>
#include <capnp/serialize-packed.h>

using namespace std;

void writeAddressBook(int fd) {
    ::capnp::MallocMessageBuilder message;

    AddressBook::Builder addressBook = message.initRoot<AddressBook>();
    ::capnp::List<Person>::Builder people = addressBook.initPeople(2);

    Person::Builder alice = people[0];
    alice.setName("Alice");
    alice.setEmail("alice@example.com");
    // Type shown for explanation purposes; normally you'd use auto.
    ::capnp::List<Person::PhoneNumber>::Builder alicePhones =
            alice.initPhones(1);
    alicePhones[0].setNumber("555-1212");
    alicePhones[0].setType(Person::PhoneNumber::Type::MOBILE);

    Person::Builder bob = people[1];
    bob.setName("Bob");
    bob.setEmail("bob@example.com");
    auto bobPhones = bob.initPhones(2);
    bobPhones[0].setNumber("555-4567");
    bobPhones[0].setType(Person::PhoneNumber::Type::HOME);
    bobPhones[1].setNumber("555-7654");
    bobPhones[1].setType(Person::PhoneNumber::Type::WORK);

    writePackedMessageToFd(fd, message);
}

int main() {
    int fd = open("/tmp/addressbook.bin", O_WRONLY);
    writeAddressBook(fd);
    close(fd);
    return 0;
}