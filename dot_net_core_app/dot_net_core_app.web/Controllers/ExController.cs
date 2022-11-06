using Microsoft.AspNetCore.Mvc;

namespace dot_net_core_app.web.Controllers
{
    public class ExController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }

        public IActionResult NoLayout()
        {
            return View();
        }
    }
}
