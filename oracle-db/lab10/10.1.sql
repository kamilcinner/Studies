--1
create index ProductCategory_Name_IDX
on ProductCategory(ProductCategoryName);

--2
create index ProductSubcategory_Cat_IDX
on ProductSubcategory(ProductCategoryKey);

--3
create index Product_Subcategory_IDX
on Product(ProductSubcategoryKey);
