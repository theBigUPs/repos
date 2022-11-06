using dot_net_core_app.web.Models;
using Microsoft.AspNetCore.Mvc;

namespace dot_net_core_app.web.Controllers
{
    public class ProductsController : Controller
    {
        private readonly ProductRepo repo;


        public ProductsController()
        {
            repo = new ProductRepo();
            if (!repo.Products().Any())
            {
                repo.Products().Add(new() { Id = 0, Name = "test", Price = 34, Stock = 12 });
                repo.Products().Add(new() { Id = 1, Name = "tes1", Price = 345, Stock = 123 });
                repo.Products().Add(new() { Id = 2, Name = "tes2", Price = 346, Stock = 124 });
            }
        }
            


        public IActionResult Index()
        {
            var products= repo.Products();
            return View(products);
        }
    }
}
