namespace dot_net_core_app.web.Models
{
    public class ProductRepo
    {
        private List<Product> _products = new List<Product>()
        {
            (new () { Id = 0, Name = "test", Price = 34, Stock = 12 }),
            (new () { Id = 1, Name = "tes1", Price = 345, Stock = 123 }),
            (new() { Id = 2, Name = "tes2", Price = 346, Stock = 124 })

        };

        


        public List<Product> Products() => _products;
      

        public void Add(Product NewProduct)
        {
            _products.Add(NewProduct);
        }

        public void remove(int id)
        {
            var hasProduct=_products.FirstOrDefault(p => p.Id == id);
            if (hasProduct==null)
            {
                throw new Exception($"no product with this id({id})");
            }
            _products.Remove(hasProduct);
        }


        public void Update(Product UpdateProduct)
        {
            var hasProduct = _products.FirstOrDefault(p => p.Id == UpdateProduct.Id);
            if (hasProduct == null)
            {
                throw new Exception($"no product with this id({UpdateProduct.Id})");
            }

            hasProduct.Name = UpdateProduct.Name;
            hasProduct.Price = UpdateProduct.Price;
            hasProduct.Stock = UpdateProduct.Stock;

            var index = _products.FindIndex(p => p.Id == UpdateProduct.Id);
            _products[index] = hasProduct;
        }


    }
}
