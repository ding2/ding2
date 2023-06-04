/// <reference types="cypress" />

describe('Accessibility tests.', () => {

  it('Should have no accessibility violations for Global Code lang and viewport. ', () => {
    cy.visit("/");
  
    cy.get('html').should('have.attr', 'lang').should('not.be.empty')
  
    cy.get('meta[name="viewport"]').should('have.attr', 'content').should('not.be.empty')

  })
  
  it('Should have no accessibility violations for img, button, input, title and a tags.', () => {
    cy.visit("/");

   cy.get('a').should('have.attr', 'href')

   cy.get('img').should('have.attr', 'alt').should('not.be.empty')
 
   cy.get('button').should('have.attr', 'title').should('not.be.empty')

   cy.get('title').should('not.be.empty')
 
   cy.get('input').and(($input) => {
     expect($input).have.attr('type').not.empty
   })
  })
  
  it('Should have no accessibility violations on front page.', () => {
    cy.visit("/");

    cy.wait(3000)
    
    cy.injectAxe()

    cy.checkA11y(null, {
      exclude: ["#cookie_cat_statistic"],
      includedImpacts: ['critical','serious'],
      rules: {
       'label-title-only' : { enabled: false }
      }
    })
  })

  it('Should have no accessibility violations on arrangementer page.', () => {
    cy.visit("/arrangementer");

    cy.get('title').should('not.be.empty')
  
    cy.get('input').and(($input) => {
      expect($input).have.attr('type').not.empty
    })

    cy.injectAxe()

    cy.checkA11y(null, 
      {
        exclude: ['.secondary-content', '#cookie_cat_statistic'],
        includedImpacts: ['critical','serious'],
        rules: {
          'aria-allowed-attr': { enabled: false },
          'label-title-only' : { enabled: false }
        },
      },
    );
  })

  it.only('Should have no accessibility violations on biblioteker page.', () => {
    cy.visit("/search/ting/belle?");
   
    cy.get('h1').should('not.be.empty')

    cy.get('title').should('not.be.empty')
  
    cy.get('input').and(($input) => {
      expect($input).have.attr('type').not.empty
    })

    cy.injectAxe()

    cy.checkA11y(null, {
      exclude: ["#cookie_cat_statistic"],
      includedImpacts: ['critical','serious'],
      rules: {
       'label-title-only' : { enabled: false }
      }
    })
  })

  it('Should have no accessibility violations on nyheder page.', () => {
    cy.visit("/nyheder");
  
    cy.get('h1').should('not.be.empty')

    cy.get('title').should('not.be.empty')
  
    cy.get('input').and(($input) => {
      expect($input).have.attr('type').not.empty
    })
   
    cy.injectAxe()

    cy.checkA11y(null, {
      exclude: ["#cookie_cat_statistic"],
      includedImpacts: ['critical','serious'],
      rules: {
       'label-title-only' : { enabled: false }
      }
    })
  })

  it('Should have no accessibility violations on e-materialer page.', () => {
    cy.visit("/e-materialer");
   
    cy.get('h1').should('not.be.empty')

    cy.get('title').should('not.be.empty')
  
    cy.get('input').and(($input) => {
      expect($input).have.attr('type').not.empty
    })
   
    cy.injectAxe()

    cy.checkA11y(null, {
      exclude: ["#cookie_cat_statistic"],
      includedImpacts: ['critical','serious'],
      rules: {
       'label-title-only' : { enabled: false }
      }
    })
  })

  it('Should have no accessibility violations on vi-tilbyr page.', () => {
    cy.visit("/vi-tilbyder");

    cy.get('h1').should('not.be.empty')

    cy.get('a').should('have.attr', 'href')

    cy.get('title').should('not.be.empty')
   
    cy.injectAxe()

    cy.checkA11y(null, {
      exclude: ["#cookie_cat_statistic"],
      includedImpacts: ['critical','serious'],
      rules: {
       'label-title-only' : { enabled: false }
      }
    })
  })

  it('Should have no accessibility violations on vi-tilbyr page.', () => {
    cy.visit("/biblioteker");

    cy.get('h1').should('not.be.empty')

    cy.get('title').should('not.be.empty')

    cy.injectAxe()

    cy.checkA11y(null, {
      exclude: ["#cookie_cat_statistic"],
      includedImpacts: ['critical','serious'],
      rules: {
       'label-title-only' : { enabled: false }
      }
    })
  })
})
