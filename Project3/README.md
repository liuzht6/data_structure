This program administrates several families and their member.  
A member has its child, parents and he/she can marry with others.

# Fundamental Function
1. Add/delete member
2. Marriage with each member
3. Print the family
4. Search each member's parents, wife(only one) and children

# Design
## class `FamilyAgenda`
### Public Method
- `Family& queryFamilyByName(const string& familyName)`, query a family name
- `Family& creatFamily()`, creat a family
- `void removeFamily(Family&)`, remove a family
### Privare Member
- `set<Family*> Families`, the set of families


## class `Family` 
### Private Method
- `void creatFamilyMember(Person& child)`, a child get born. When a child born, this child adds to his/her parents family
- `void addFamilyMember(Person& husband)`, add a family member. When a family male gets married with other family's female, that female adds to her husband's family
- `void removeFamilyMember(string& name)`, delete a family member. When a family female gets married with other family's male, that female will be removed
### Public Method
- `vector<Person*> queryFamilyMemberByName(string& name)`, query a family member by name
- `void familyStatistic()`, output the family's statistics information
- `void marryWith(Person&)`
### Private Member
- `Person* founder`, the founder of this family
- `int familyMemberNumber`, total number of members in this family
- `string familyName`

## struct `Person`
### Member
- `Person* partner`, partner of this person
- `vector<Person*> children`, this person's children
- `Person* father`, father of this person
- `Person* mather`, mather of this person
- `vector<Person*> sibling`, this person's siblings
- `string familyName`, the person's family name


# To-do list
1. Definition of family tree (liuzht)
2. Guide menu of this agenda (Ken-Redevil)
3. Program test (Ecer23)
4. Project report (Work together)
5. Web or application(optional)


