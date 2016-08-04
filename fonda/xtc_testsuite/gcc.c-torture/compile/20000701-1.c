void
dr106_1(void *pv, int i)
{
	*pv;           // {{ dg-warning "dereferencing" }}
	i ? *pv        // {{ dg-warning "dereferencing" }}
          : *pv;       // {{ dg-warning "dereferencing" }}
	*pv,           // {{ dg-warning "dereferencing" }}
          *pv;         // {{ dg-warning "dereferencing" }}
}

void
dr106_2(const void *pcv, volatile void *pvv, int i)
{
	*pcv;             // {{ dg-warning "dereferencing" }}
	i ? *pcv          // {{ dg-warning "dereferencing" }}
          : *pcv;         // {{ dg-warning "dereferencing" }}
	*pcv,             // {{ dg-warning "dereferencing" }}
          *pcv;           // {{ dg-warning "dereferencing" }}

	*pvv;             // {{ dg-warning "dereferencing" }}
	i ? *pvv          // {{ dg-warning "dereferencing" }}
          : *pvv;         // {{ dg-warning "dereferencing" }}
	*pvv,             // {{ dg-warning "dereferencing" }}
          *pvv;           // {{ dg-warning "dereferencing" }}
}
